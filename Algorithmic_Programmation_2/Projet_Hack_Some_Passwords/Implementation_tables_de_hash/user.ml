(**
  Module rassemblant les implémentations concernant l'utilisateur.
  @author Thomas Neupont
  @author Noé Bordas
*)

(**
  Fonction qui ajoute les utilisateurs dans la table des utilisateurs connus
  [t_known_user list].
  @author Thomas Neupont
  @author Noé Bordas
  @param login : string
  @param pwd : string
  @param table_known_user : [Hashtbl]
*)
let add_to_known_user(login, pwd, table_known_user) : unit = 
  if Hashtbl.mem table_known_user login then
    (
      let curr_list = Hashtbl.find table_known_user login in
      (
        Hashtbl.replace table_known_user login (pwd :: curr_list)
      )
    )
  else
    (
      Hashtbl.add table_known_user login [pwd]
    )
;;

(**
  Fonction qui ajoute une liste d'utilisateurs dont on connais les mots de passe en clair à la table de hash des utilisateurs connus.
  @author Thomas Neupont
  @author Noé Bordas
  @param list_user : (string * string) list
  @param known_user : [Hashtbl]
  @return unit
*)
let make_known_user_list(list_user, known_users) : unit = 
  let list_users : (string * string) list ref = ref list_user in (
    while !list_users <> [] do (
      let (u_log, u_pwd) = List.hd(!list_users) in (
        add_to_known_user(u_log, u_pwd, known_users);
        list_users := List.tl(!list_users)
      )
    )done;
  )
;;

(**
  Fonction qui récupère un utilisateur dans la table de hash des utilisateurs connus.
  @author Thomas Neupont
  @author Noé Bordas
  @param login : string
  @param table_known_user : [Hashtbl]
  @return [bool * string list] : (True si l'utilisateur est connu, 
  False s'il n'est pas connu en conséquent on ne traite pas la donnée de liste des mots de passe)
*)
let get_if_known_user(login, table_known_user) : (bool * string list) =
  if Hashtbl.mem table_known_user login then (true, Hashtbl.find table_known_user login)
  else (false, [])
;;

(**
  @author Noé Bordas
  @auhtor Thomas Neupont
  @param login string
  @param table_known_user [Hashtbl]
  @return : [string list]
  Retourne une liste des mots de passes déjà connus pour un utilisateur. Si l'utilisateur n'est pas connu, renvoie une liste vide.
*)
let get_known_user(login, table_known_user): string list=
  let (success, pwds) = get_if_known_user(login, table_known_user) in
  (
    if success then pwds
    else []
  )
;;