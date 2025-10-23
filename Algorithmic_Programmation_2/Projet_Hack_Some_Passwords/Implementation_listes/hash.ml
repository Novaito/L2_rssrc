(**
  Module rassemblant les implémentations concernant le hash d'un mot passe.
  @author Thomas Neupont
  @author Noé Bordas
*)

(**
  Type permettant de stocker :
  <ul>
    <li>[hash : string] : le résultat du mot de passe crypté.</li>
    <li>[pwd : string] : l'équivalence du mot de passe en clair.</li>
  </ul>
  @author Thomas
*)
type t_known_hash = {hash : string; pwd : string} ;;

(**
  Fonction qui renvoit le mot de passe du hash déchiffré.
  @author Thomas
  @param hash_struc : [t_known_hash]
  @return [string]
*)
let get_pwd_known_hash(hash_struc) = hash_struc.pwd ;;

(**
  Fonction qui renvoit le hash d'un hash connu.
  @author Thomas
  @param hash_struc : [t_known_hash]
  @return [string]
*)
let get_hash_known_hash(hash_struc) = hash_struc.hash ;;

(**
  Fonction qui transforme la donnée du hash en type structuré.
  @author Thomas
  @param hash : string
  @param pwd : string
  @return [t_known_hash]
*)
let make_known_hash(hash, pwd) : t_known_hash = {hash = hash; pwd = pwd} ;;

(**
  Fonction qui ajoute les utilisateurs de type [t_known_hash] dans une liste de type
  [t_known_hash list].
  Temps : O(n) Spatiale: O(n)
  @author Thomas
  @param login : string
  @param pwd : string
  @param list_known_hash : [t_known_hash list]
*)
let add_to_known_hash(hash, pwd, list_known_hash) : unit = 
  let list_new = ref []
  and found = ref false in (
    while !list_known_hash <> [] && not(!found) do (
      let hash_var = List.hd(!list_known_hash) in (
        if hash_var.hash = hash then found := true
        else (
          if hash_var.hash > hash then (
            list_new := make_known_hash(hash, pwd) :: !list_new ;
          found := true
          ) else (
            list_new := hash_var :: !list_new;
            list_known_hash := List.tl(!list_known_hash)
          )
        )
      )
    )done;
    if not(!found) then (
      list_new := make_known_hash(hash, pwd) :: !list_new
    );
    list_new := reverse_list(!list_new) ;
    list_known_hash := !list_new @ !list_known_hash
  )
;;

(**
  Fonction qui récupère mots de passes dans [t_known_hash]. 
  Temps : O(n) Spatiale: O(1)
  @author Thomas
  @param hash : string
  @param [list_known_hash] : [t_known_hash list]
  @return [bool * t_known_hash] : (True si le hash est connu, 
  False s'il n'est pas connu en conséquent on ne traite pas la donnée de t_known_hash)
*)
let get_known_hash(hash, list_known_hash : string * t_known_hash list) : (bool * t_known_hash) =
  let list_hashes = ref list_known_hash
  and found = ref false in (
    let res = ref {hash=""; pwd=""} in (
      while not(!found) && !list_hashes <> [] do (
        let hash_struc = List.hd(!list_hashes) in (
          if hash_struc.hash = hash then (
            found := true ;
            res := hash_struc
          )
          else (
            list_hashes := List.tl(!list_hashes)
          )
        )
      )done;
      (!found, !res)
    )
  )
;;

(**@author Noé Bordas
@param common_pwd string * list
@param known_hash t_known_hash ref
Ajoute tous les mots de passes les plus communs en france à la liste des mots de passes connus.
Temps : O(n) Spatiale: O(m) Avec m la longueur de common_pwd*)
let add_all_common_pwd_to_known_hash(common_pwd, known_hash : (string) list * t_known_hash list ref): unit=
  let tl_common = ref common_pwd
  in
  (
    while not(!tl_common = []) do
      let hash = hash_password(List.hd(!tl_common)) in
      (
        add_to_known_hash(hash, List.hd(!tl_common), known_hash);
        tl_common := List.tl(!tl_common)
      )
    done
  )
;;