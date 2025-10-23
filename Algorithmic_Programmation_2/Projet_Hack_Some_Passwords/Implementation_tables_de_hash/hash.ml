(**
  Module rassemblant les implémentations concernant le hash d'un mot passe.
  @author Thomas Neupont
  @author Noé Bordas
*)

(**
  Fonction qui ajoute un hash connu dans la table de hash des utilisateurs connus.
  @author Thomas Neupont
  @author Noé Bordas
  @param login : string
  @param pwd : string
  @param table_known_hash : [Hashtbl]
*)
let add_to_known_hash(hash, pwd, table_known_hash) : unit = 
  if not(Hashtbl.mem table_known_hash hash) then Hashtbl.add table_known_hash hash pwd
;;

(**
  Fonction qui récupère un hash dans la table des hashs connus
  @author Thomas Neupont
  @author Noé Bordas
  @param hash : string
  @param [table_known_hash] : [Hashtbl]
  @return [bool * t_known_hash] : (True si le hash est connu, 
  False s'il n'est pas connu en conséquent on ne traite pas la donnée de t_known_hash)
*)
let get_known_hash(hash, table_known_hash) : (bool * string) =
  if Hashtbl.mem table_known_hash hash then (true, Hashtbl.find table_known_hash hash)
  else (false, "")
;;

(**@author Noé Bordas
@author Thomas Neupont
@param common_pwd string * list
@param known_hash : [Hashtbl]
Ajoute tous les mots de passes les plus communs en france à la table de hash des hashs connus.*)
let add_all_common_pwd_to_known_hash(common_pwd, known_hash): unit=
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
