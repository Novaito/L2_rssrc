(**
  Ce module main représente l'utilisation d'un outil pour récupérer des mots de passes 
  d'utilisateurs à partir d'une fuite de données. L'extension de fichier supporté est {b .txt}
  et ne doit être constitué que d'un login et de son mot de passe sur la ligne suivante.
  @author Thomas Neupont
  @author Noé Bordas
  @version 4.1.1
*)

#use "app.ml" ;;
(**
  Fonction principale qui se charge d'effectuer toutes instructions nécessaires.
  @author Thomas Neupont
  @author Noé Bordas
*)
let main() : unit = 
  let all_users_known = Hashtbl.create 10000
  and all_hash_known = Hashtbl.create 30000
  and list_result : (string * string * string) list ref = ref []
  and len_total_user_to_find = List.length (fusion_file ([|"slogram01.txt"; "slogram02.txt"|])) + List.length(fusion_file([|"tetedamis01.txt"; "tetedamis02.txt"|]))
  and all_frenchpassword = read_list_from_file("french_passwords_top20000.txt")
  and all_users_depensetout = fusion_file([|"depensetout01.txt" ; "depensetout02.txt"|])
  and app_tab : t_application array = [|
    {name="slogram"; source=[|"slogram01.txt" ; "slogram02.txt"|]} ;
    {name="tetedamis"; source=[|"tetedamis01.txt" ; "tetedamis02.txt"|]}
  |] in (
    add_all_common_pwd_to_known_hash(all_frenchpassword, all_hash_known);
    make_known_user_list(all_users_depensetout, all_users_known) ;
    result inject_with_app(app_tab, all_users_known, all_hash_known) len_total_user_to_find list_result
  )
;;

main() ;;