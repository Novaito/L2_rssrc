(**
  Module de divers outils permettant l'implémentation de certains modules, mais aussi
  au debug.
  @author Thomas Neupont
  @author Noé Bordas
*)

#use "topfind";;
#require "cryptokit";;
#require "base64";;

let read_data_from_file file =
  let f = open_in file in
  let rec aux acc =
    try
      let login = input_line f 
      and pwd = input_line f
       in
        aux ((login, pwd) :: acc)
    with End_of_file ->
      close_in f;
    List.rev acc
  in
  aux []
;;

let read_list_from_file file =
  let f = open_in file in
  let rec aux acc =
    try
      let pwd = input_line f 
        in
        aux (pwd :: acc)
    with End_of_file ->
      close_in f;
    List.rev acc  
  in
  aux []
;;
  
let hash_password pwd =
  Base64.encode_exn(Cryptokit.hash_string (Cryptokit.Hash.sha256 ()) pwd)
;;

(**
  Fonction récupérée du TP3 afin d'estimer le temps d'exécution de nos algorithmes
  et affiche le nombre d'utilisateur trouvé sur le nombre total récupéré.
  @author Thomas (modified)
*)
let result f x n_total list: unit =
  let t = Sys.time() in (
    let fx = f x in (
      list := fx ;
      let n_found = List.length(!list) in (
        Printf.printf "%d/%d users found in %fs\n" n_found n_total (Sys.time() -. t);
      )
    )
  )
;;

(**
  Fonction qui affiche l'application le login et le mdp.
  @author Thomas noé
  @param app : string
  @param log : string
  @param pwd : string
*)
let printpwd(app, log, pwd) : unit =
  Printf.printf "%s %s %s \n" app log pwd
;;

(**
Ecrit le résultat sous forme de liste de tuple de 3 strings dans un fichier donné en paramètre
@author Noé Bordas
@param file : string, le chemin vers le fichier de sortie
@param res : (string * string * string) list, le résultat de la recherche de mots de passe.*)

let write_result_to_file file res =
  let f = open_out file
  and tl_res = ref res in
  (
    while not(!tl_res = []) do
      let (app, log, pwd) = List.hd(!tl_res) in
      (
        Printf.fprintf f "%s, %s, %s\n" app log pwd
      );
      tl_res := List.tl(!tl_res)
    done;
    close_out f
  )
;;