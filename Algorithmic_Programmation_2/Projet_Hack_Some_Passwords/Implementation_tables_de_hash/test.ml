#use "app.ml";;

let all_hash_known = Hashtbl.create 1000000;;
let all_frenchpassword = read_list_from_file("french_passwords_top20000.txt");;
add_all_common_pwd_to_known_hash(all_frenchpassword, all_hash_known);;
10;;


let generatePasswords(known_hash)=
  let words = ref (read_list_from_file "liste_francais.txt") in
  (
    while not(!words = []) do
      for i=0 to 99 do
        for j=33 to 47 do
          let word = (String.trim (List.hd(!words))) ^ string_of_int(i) ^ (String.make 1 (char_of_int(j))) in
          (
            add_to_known_hash(hash_password(word), word, known_hash)
          )
        done;
      done;
      words := List.tl(!words)
    done
  )
;;

generatePasswords(all_hash_known)

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