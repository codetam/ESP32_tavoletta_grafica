<?php

/* Verifica che tutto sia corretto e in caso contrario invia errori alla pagina precedente tramite GET */
if(isset($_POST["submit"])){

    $uid = $_POST["uid"];
    $pwd = $_POST["pwd"];

    require_once "db.access.php";
    require_once "functions.general.php";
    
    if(emptyInputLogin($uid,$pwd) === true){
        header("location: ../login.php?error=empty_fields");
        exit();
    }
    if(loginUser($conn,$uid,$pwd) === false){
        header("location: ../login.php?error=invalid_credentials");
        exit();
    }
    else{
        $row = uidExists($conn, $uid);
        session_start();
        $_SESSION["uid"] = $row["userName"];
        header("location: ../profile.php");
        exit();
    }
}
else {
    header("location: ../login.php");
    exit();
 }