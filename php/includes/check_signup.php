<?php

/* Verifica che tutto sia corretto e in caso contrario invia errori alla pagina precedente tramite GET */
if (isset($_POST["submit"])) {
    $uid = $_POST["uid"];
    $pwd = $_POST["pwd"];
    $pwdrepeat = $_POST["pwdrepeat"];

    require_once "db.access.php";
    require_once "functions.general.php";

    if (emptyInputSignup($uid, $pwd, $pwdrepeat) !== false) {
        header("location: ../signup.php?error=empty_fields");
        exit();
    }
    if (pwdDontMatch($pwd, $pwdrepeat) !== false) {
        header("location: ../signup.php?error=pwd_not_matching");
        exit();
    }
    if (invalidUid($uid) !== false) {
        header("location: ../signup.php?error=invalid_username");
        exit();
    }
    if (uidExists($conn, $uid) !== false) {
        header("location: ../signup.php?error=existing_username");
        exit();
    }
    if(createUser($conn, $uid, $pwd) === false){
        header("location: ../signup.php?error=system_error");
        exit();
    }
    else{
        $row = uidExists($conn, $uid);
        session_start();
        $_SESSION["uid"] = $row["userName"];
        header("location: ../signup.php?error=none");
    }
} 
else {
    header("location: ../signup.php");
    exit();
}