<?php

/* 
   Ritorna lo status code 200 e la stringa dell'immagine associata
   solo se le credenziali corrispondono
*/
if(isset($_POST['uid']) && isset($_POST['pwd']) && isset($_POST["imageId"])){
    
    $username = $_POST['uid'];
    $pwd = $_POST['pwd'];
    $imgId = $_POST["imageId"];

    require_once '../includes/db.access.php';
    require_once '../includes/functions.general.php';

    if( emptyInputLogin($username, $pwd) === true ){
        http_response_code(400);
        exit();
    }

    if( loginUser($conn, $username, $pwd) !== true ){
        http_response_code(401);
        exit();
    }

    if($string_to_send = getImageFromId($conn, $imgId)){
        http_response_code(200);
        echo $string_to_send;
        exit();
    }
    else{
        http_response_code(400);
        exit();
    }
}
else {
    http_response_code(400);
    exit();
}