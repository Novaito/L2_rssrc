(**
  Module rassemblant les fonctions qui gèrent l'implémentation
  de tous les modules utiles pour mener à bien l'experimentation.
  @author Thomas Neupont
  @author Noé Bordas
*)

#use "tools.ml" ;;
#use "gather.ml" ;;
#use "user.ml" ;;
#use "hash.ml" ;;

(**
  Type structuré permettant d'avoir plusieurs fichiers textes
  de fuites de données par applications et aussi pouvoir récupérer le
  nom de l'application lorsqu'un mot de passe et trouvé.
  @author Thomas Noé
*)
type t_application = {name: string; source: string array} ;;

(**
  Fonction renvoyant le nom de l'app.
  @author Thomas
  @param app : [t_application]
  @return string
*)
let get_name_app(app) = app.name ;;

(**
  Fonction qui renvoit la liste de fichiers de l'app.
  @author Thomas
  @param app : [t_application]
  @return string array
*)
let get_source_app(app) = app.source ;;

(**
  @author Noé Bordas
  @param hash : string
  @param pwd : string
  @return : bool
  Renvoie True si string pwd en paramètre est, une fois hashé, égal au string hash
*)
let try_hash_pwd(hash, pwd : string * string): bool=
  hash = hash_password(pwd)
;;

(**
  @author Noé Bordas
  @param hash : string
  @param pwd : string list
  @return bool * string
  Teste la correspondance d'une liste de mots de passe avec un hash. Renvoie si une correspondance est trouvée et si oui le mot de passe. Sinon, un string vide.
*)
let try_hash_pwds(hash, pwds : string * string list): bool * string=
  let tail = ref pwds
  and res = ref ""
  and found = ref false in
  (
    while not(!tail = []) && not(!found) do
      if try_hash_pwd(hash, List.hd(!tail)) then
        (
          found := true;
          res := List.hd(!tail)
        )
      else tail := List.tl(!tail) 
    done;
    (!found, !res)
  )
;;

(**
  @author Noé Bordas
  @param login : string
  @param hash : string
  @param list_known_user : string
  @return : (bool * string)
  Essaie de trouver le mot de passe correspondant au hash en comparant avec les autres mot de passe d'un même login.
*)
let try_known_user(login, hash, list_known_user): (bool * string) =
  let known_user_password = get_known_user(login, list_known_user) in 
  (
    try_hash_pwds(hash, known_user_password)
  )
;;

(**
  Fonction qui cherche si le hash est connu dans la liste [t_known_hash list].
  @author Thomas
  @param hash
  @param list_known_hash : [t_known_hash list]
  @return [bool * string] : true/false si trouvé + le mdp en clair si true.
*)
let try_known_hash(hash, list_known_hash) : (bool * string) =
  let (res, hash) = get_known_hash(hash, list_known_hash) in (
    if res then (
      (true, hash)
    ) else (
      (false, "")
    )
  )
;;

(**
  Fonction qui effectue les recherches de toutes les façons possible d'obtenir
  le mot de passe en clair d'un utilisateur.
  @author Thomas
  @param login : string
  @param hash : string
  @param list_known_user : [t_known_hash list]
  @return [bool * string] : true/false si trouvé et ajouté + le mdp en clair si true.
*)
let find_pwd_user(login, hash, list_known_user, list_known_hash) : bool * string =
  let (res, pwd) = try_known_user(login, hash, list_known_user) in (
    if res then (
      add_to_known_hash(hash, pwd, list_known_hash) ;
      (res, pwd)
    )
    else (
      let (res, pwd) = try_known_hash(hash, list_known_hash) in (
        if res then (
          add_to_known_user(login, pwd, list_known_user);
          (res, pwd)
        )
        else (
          (false, "")  
        )
      )
    )
  )
;;

(**
  Fonction qui permet d'ajouter les utilisateurs trouvés dans une liste de
  forme (nom app, login, mdp).
  @author Thomas
  @param app_name : string
  @param users : (string * string) list
  @param list_known_user : [t_known_user]
  @param list_known_known_hash : [t_known_hash]
  @return [(string * string * string) list] : (nom app, login, mdp)
*)
let get_all_pwd(app_name, users_app, list_known_user, list_known_hash) : (string * string * string) list =
  let all_users_found = ref []
  and list_users = ref users_app in (
    while !list_users <> [] do (
      let (u_log, u_hash) = List.hd(!list_users) in (
        let (res, pwd) = find_pwd_user(u_log, u_hash, list_known_user, list_known_hash) in (
          if res then (
            all_users_found := (app_name, u_log, pwd) :: !all_users_found
          )
        );
        list_users := List.tl(!list_users)
      )
    )done;
    !all_users_found
  )
;;

(**
  Fonction qui automatise la recherche de mots de passes sur 
  plusieurs applications différentes, et renvoit une liste globale 
  avec les résultats obtenus pour toutes les applications.
  @author Thomas
  @param app_tab [t_application array]
  @param list_known_user : [t_known_user]
  @param list_known_hash : [t_known_hash]
  @return [(string * string * string) list] (nom app, login, mdp)
*)
let inject_with_app(app_tab, list_known_user, list_known_hash) : (string * string * string) list =
  let len = Array.length(app_tab)
  and list_res = ref [] in (
    for i=0 to len-1 do (
      let app_name = get_name_app(app_tab.(i))
      and app_files = get_source_app(app_tab.(i)) in (
        let all_users_in_file = fusion_file(app_files) in (
          list_res := !list_res @ get_all_pwd(app_name, all_users_in_file, list_known_user, list_known_hash)
        )
      )
    )done;
    write_result_to_file "output.txt" !list_res;
    !list_res
  )
;;