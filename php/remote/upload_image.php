<?php

/* Ritorna lo status code 200 solo se l'immagine è stata salvata con successo */
if( isset($_POST['uid']) && isset($_POST['pwd']) && isset($_POST['sent_image']) ){
    $username = $_POST["uid"];
    $pwd = $_POST["pwd"];
    $image = $_POST["sent_image"];

    require_once '../includes/db.access.php';
    require_once '../includes/functions.general.php';

    if( emptyInputLogin($username, $pwd) === true || strlen($image) !== 9600 ){
        http_response_code(400);
        exit();
    }

    if( loginUser($conn, $username, $pwd) !== true ){
        http_response_code(401);
        exit();
    }

    if( uploadImage($conn, $username, $image) === true ){
        http_response_code(200);
        exit();
    }
    else {
        http_response_code(500);
        exit();
    }
}
else {
    http_response_code(400);
    exit();
}
