<?php

if (isset($_POST['uid']) && isset($_POST['pwd']) && isset($_POST['action'])) {
    $username = $_POST["uid"];
    $pwd = $_POST["pwd"];

    require_once '../includes/db.access.php';
    require_once '../includes/functions.general.php';

    if (emptyInputLogin($username, $pwd) === true) {
        http_response_code(400);
        exit();
    }
    if ($_POST['action'] == 'login') {
        // Login button was clicked
        if (loginUser($conn, $username, $pwd) === true) {
            http_response_code(200);
        } else {
            http_response_code(401);
        }
        exit();
    } 
    elseif ($_POST['action'] == 'signup') {
        // Signup button was clicked
        if (invalidUid($username) !== false) {
            http_response_code(401);
            exit();
        }
        if (uidExists($conn, $username) !== false) {
            http_response_code(400);
            exit();
        }
        if (createUser($conn, $username, $pwd) !== false) {
            http_response_code(200);
        }
        else{
            http_response_code(500);
        }
    }
    else{       
        http_response_code(400);
    }
} 
else {
    http_response_code(400);
}
exit();