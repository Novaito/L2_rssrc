(**
  Module rassemblant les implémentations concernant l'utilisateur.
  @author Thomas Neupont
  @author Noé Bordas
*)

(**
  Type permettant de stocker :
  <ul>
    <li>[login : string] : le login d'un utilisateur.</li>
    <li>[pwd_list : string list] : la liste mutable de la totalité de ses mots de passes.</li>
  </ul>
  @author Thomas
*)
type t_known_user = {login : string; mutable pwd_list : string list} ;;

(**
  Fonction qui renvoit le login d'un utilisateur.
  @author Thomas
  @param user : [t_known_user]
  @return [string]
*)
let get_login_known_user(user) = user.login ;;

(**
  Fonction qui renvoit la liste de mots de passes connus d'un utilisateur.
  @author Thomas
  @param user : [t_known_user]
  @return [string list] : string list
*)
let get_pwd_known_user(user) = user.pwd_list ;;

(**
  Fonction qui transforme la donnée de l'utilisateur du fichier en type structuré.
  @author Thomas
  @param log : string
  @param pwd : string
  @return [t_known_user]
*)
let make_known_user(log, pwd) : t_known_user = {login = log; pwd_list = [pwd]} ;;

(**
  Fonction qui ajoute les utilisateurs de type [t_known_user] dans une liste de type
  Temps : O(n) Spatiale: O(n)
  [t_known_user list].
  @author Thomas & Noé
  @param login : string
  @param pwd : string
  @param list_known_user : [t_known_user list]
*)
let add_to_known_user(login, pwd, list_known_user) : unit = 
  let list_new = ref []
  and found = ref false in (
    while !list_known_user <> [] && not(!found) do (
      let user_var = List.hd(!list_known_user) in (
        if user_var.login = login then (
          if not(pwd_in_list(pwd, user_var.pwd_list, false)) then (
            user_var.pwd_list <- pwd :: user_var.pwd_list ; 
            found := true
          )
        ) else (
          if user_var.login > login then (
            list_new := make_known_user(login, pwd) :: !list_new ;
            found := true
          ) else (
            list_new := user_var :: !list_new;
            list_known_user := List.tl(!list_known_user)
          )
        )
      )
    )done;
    if not(!found) then (
      list_new := make_known_user(login, pwd) :: !list_new
    );
    list_new := reverse_list(!list_new) ;
    list_known_user := !list_new @ !list_known_user
  )
;;

(**
  Fonction qui créé la liste d'utilisateurs sous forme de type structuré et y ajoute les utilisateurs.
  Temps : O(n) Spatiale : O(n)
  @author Thomas
  @param list_known_user : (string * string) list
  @return [t_known_user list]
*)
let make_known_user_list(list_known_user : 'a list) : t_known_user list = 
  let list_users : (string * string) list ref = ref list_known_user
  and list_t_known_user : t_known_user list ref = ref [] in (
    while !list_users <> [] do (
      let (u_log, u_pwd) = List.hd(!list_users) in (
        list_t_known_user := make_known_user(u_log, u_pwd) :: !list_t_known_user;
        list_users := List.tl(!list_users)
      )
    )done;
    list_t_known_user := reverse_list(!list_t_known_user) ;
    !list_t_known_user
  )
;;

(**
  Fonction qui récupère l'utilisateur dans [t_known_user list].
  Temps : O(n) Spatiale: O(1)
  @author Thomas
  @param login : string
  @param list_known_user : [t_known_user list]
  @return [bool * t_known_user] : (True si l'utilisateur est connu, 
  False s'il n'est pas connu en conséquent on ne traite pas la donnée de t_known_user)
*)
let get_if_known_user(login, list_known_user : string * t_known_user list) : (bool * t_known_user) =
  let list_users = ref list_known_user
  and found = ref false in (
    let res = ref (List.hd(!list_users)) in (
      while not(!found) && !list_users <> [] do (
        let user_struc = List.hd(!list_users) in (
          if user_struc.login = login then (
            found := true ;
            res := user_struc
          )
          else (
            list_users := List.tl(!list_users)
          )
        )
      )done;
      (!found, !res)
    )
  )
;;

(**
  @author Noé Bordas
  @param login string
  @param list_known_user t_known_user list
  @return : string list
  Retourne une liste des mots de passes déjà connus pour un utilisateur. Si l'utilisateur n'est pas connu, renvoie une liste vide.
  Temps: O(n) Spatiale: O(1)
*)
let get_known_user(login, list_known_user : string * t_known_user list): string list=
  let (success, user) = get_if_known_user(login, list_known_user) in
  (
    if success then user.pwd_list
    else []
  )
;;