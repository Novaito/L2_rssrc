(**
  Module ayant pour fonction de restructurer les données de fichiers
  pour les epxloiter par la suite.
  @author Thomas Neupont
  @author Noé Bordas
*)



(**
  @author Noé Bordas
  @param p_l Une liste quelconque
  @return Une copie de la liste inversée
*)
let reverse_list(p_l : 'a list): 'a list=
  let res = ref []
  and tail = ref p_l in
  (
    while not(!tail = []) do 
      res := List.hd(!tail) :: !res;
      tail := List.tl(!tail)
    done;
    !res
  )
;;

(**
  @author Noé Bordas
  @param p_l Une liste quelconque
  @param m Un entier plus petit que la longuer de la liste moins 1
  @return Deux listes issues de la liste en paramètre
  Sépare une liste en deux liste différentes à partir du m ième élément 
*)
let split_list (p_l, m: 'a list * int): 'a list * 'a list=
  let first_half = ref []
  and second_half = ref p_l in
  (
    for i = 0 to m do
      first_half := List.hd(!second_half) :: !first_half;
      second_half := List.tl(!second_half)
    done;
    (reverse_list(!first_half), reverse_list(!second_half))
  )
;;

(**
  @author Noé Bordas
  @param p_l1 Une liste de couple quelconques triés selon le premier élément du couple
  @param p_l2 Une liste de couple quelconques triés selon le premier élément du couple
  @return Une liste de couple triée selon le premier élément du couple
  Fusionne les deux listes en paramètres déjà triées selon le premier élément du couple
*)
let fusion_part_list (p_l1 , p_l2 : ('a * 'b) list * ('a * 'b) list): ('a * 'b) list = 
  let tl_1 = ref p_l1
  and tl_2 = ref p_l2
  and res = ref [] in
  (
    while not(!tl_1 = []) && not(!tl_2 = []) do
      if fst(List.hd(!tl_1)) <= fst(List.hd(!tl_2)) then
        (
          res := List.hd(!tl_1) :: !res;
          tl_1 := List.tl(!tl_1)
        )
      else
        (
          res := List.hd(!tl_2) :: !res;
          tl_2 := List.tl(!tl_2)
        )
    done;

    if !tl_2 = [] then
      (
        while not(!tl_1 = []) do 
          res := List.hd(!tl_1) :: !res;
          tl_1 := List.tl(!tl_1)
        done;
        reverse_list(!res);
      )
    else
      (
        while not(!tl_2 = []) do 
          res := List.hd(!tl_2) :: !res;
          tl_2 := List.tl(!tl_2)
        done;
        reverse_list(!res)
      )
  )
;;

(**
  @author Noé Bordas
  @param p_list Une liste de couple
  @return La liste de couple donné en paramètre triée selon le premier élément du couple
*)
let tri_fusion_list(p_list : ('a * 'b) list): ('a * 'b) list=
  (**
  @param p_list Une liste de couple
  @param len La longueur de la liste donnée en paramètre
  @return Une copie de la liste originale triée selon le premier élément du couple*)
  let rec tri_fusion_list_aux(p_l, len  : ('a * 'b) list * int): ('a * 'b) list =
    if len = 1 then p_l
    else
      (
        let m = ((len - 1) / 2) in 
        (
          let (first_half, second_half) = split_list(p_l, m) in
          (
            fusion_part_list(tri_fusion_list_aux(first_half, m + 1), tri_fusion_list_aux(second_half, len - m - 1))
          )
        )
      )
    in
    (
      tri_fusion_list_aux(p_list, List.length(p_list))
    )
;;

(**
  @author Noé Bordas
  @param p_l1 Une liste de couple triée selon le premier élément du couple
  @param p_l2 Une liste de couple triée selon le premier élément du couple
  @return Une liste de couple triée resultat de la fusion des deux listes en paramètres avec la suppression des doublons 
*)
let fusion_two_couple_lists(p_l1, p_l2 : ('a * 'b) list * ('a * 'b) list): ('a * 'b) list=
  let tl_1 = ref p_l1
  and tl_2 = ref p_l2
  and res = ref [] in
  (
    while not(!tl_1 = []) && not(!tl_2 = []) do
      if fst(List.hd(!tl_1)) = fst(List.hd(!tl_2)) then
        (
          res := List.hd(!tl_1) :: !res;
          tl_1 := List.tl(!tl_1);
          tl_2 := List.tl(!tl_2)
        )
      else
        (
          if fst(List.hd(!tl_1)) < fst(List.hd(!tl_2)) then
            (
              res := List.hd(!tl_1) :: !res;
              tl_1 := List.tl(!tl_1)
            )
          else
            (
              res := List.hd(!tl_2) :: !res;
              tl_2 := List.tl(!tl_2)
            )
        )
    done;
    
    if !tl_2 = [] then
      (
        while not(!tl_1 = []) do 
          res := List.hd(!tl_1) :: !res;
          tl_1 := List.tl(!tl_1)
        done;
        reverse_list(!res);
      )
    else
      (
        while not(!tl_2 = []) do 
          res := List.hd(!tl_2) :: !res;
          tl_2 := List.tl(!tl_2)
        done;
        reverse_list(!res)
      )
    
  )
;;

(**
  @author Noé Bordas
  @param p_t Un tableau de liste de couples triées selon le premier élément du couple
  @return Une liste de couple triée selon le premier élément du couple avec les doublons supprimés
  Appele la fonction fusion_two_couple_lists pour tous les éléments du tableau entre eux
*)
let fusion_multiple_couple_lists(p_t : ('a * 'b) list array) : ('a * 'b) list=
  let res = ref p_t.(0)
  and len = Array.length(p_t) in
  (
    for i = 1 to len - 1 do
      res := fusion_two_couple_lists(!res, p_t.(i))
    done;

    !res
  )
;;

(**
  @author Noé Bordas
  @param file_list Un tableau contenant les nom des fichier contenant une ligne d'identifiant suivit d'une ligne de mot de passe
  @return Tous les couples indentifiant mot de passes uniques présents dans les fichiers en paramètres
  Renvoie la liste de tous les couples indentifiant mot de passes triés avec les doublons fusionnés.
*)
let fusion_file(file_list : string array): (string * string) list=
  let file_number = Array.length(file_list) in
  let files = Array.make file_number [] in
  (
    for i = 0 to file_number -1 do
      files.(i) <- tri_fusion_list(read_data_from_file file_list.(i))
    done;

    fusion_multiple_couple_lists(files)
  )
;;

(**
  Fonction utilitaire de [add_to_known_aux] vérifiant si le mot de passe en argument est
  déjà connu dans la liste de mot de passe de l'utilisateur.
  @author Thomas
  @param pwd : string
  @param list_pwd : string list
  @return [bool]
*)
let rec pwd_in_list(pwd, list_pwd, found) : bool =
  if list_pwd = [] then found
  else (
    if List.hd(list_pwd) = pwd then true
    else pwd_in_list(pwd, List.tl(list_pwd), found)
  )
;;