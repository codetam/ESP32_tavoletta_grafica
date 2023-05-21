<?php

function createUser($conn, $uid, $pwd)
{
    $sql = "INSERT INTO users (userName,userPwd) VALUES(?,?);";
    $stmt = mysqli_stmt_init($conn);

    if (!mysqli_stmt_prepare($stmt, $sql)) {
        return false;
    }

    $hashedPwd = password_hash($pwd, PASSWORD_DEFAULT);
    mysqli_stmt_bind_param($stmt, "ss", $uid, $hashedPwd);
    mysqli_stmt_execute($stmt);
    mysqli_stmt_close($stmt);
    return true;
}


function emptyInputSignup($uid, $pwd, $pwdrepeat)
{
    if (empty($uid) || empty($pwd) || empty($pwdrepeat)) {
        return true;
    } else {
        return false;
    }
}

function pwdDontMatch($pwd, $pwdrepeat)
{
    if ($pwd !== $pwdrepeat) {
        return true;
    } else {
        return false;
    }
}

function invalidUid($uid)
{
    if (!preg_match("/^[a-zA-Z0-9]*$/", $uid)) {
        return true;
    } else {
        return false;
    }
}

function emptyInputLogin($username, $pwd)
{
    if (empty($username) || empty($pwd)) {
        return true;
    } else {
        return false;
    }
}

function uidExists($conn, $username)
{
    $sql = "SELECT * FROM users WHERE userName = ?;";
    $stmt = mysqli_stmt_init($conn);
    if (!mysqli_stmt_prepare($stmt, $sql)) {
        return false;
    }
    mysqli_stmt_bind_param($stmt, "s", $username);
    mysqli_stmt_execute($stmt);
    $resultData = mysqli_stmt_get_result($stmt);

    if ($row = mysqli_fetch_assoc($resultData)) {
        mysqli_stmt_close($stmt);
        return $row;
    } else {
        mysqli_stmt_close($stmt);
        return false;
    }
}

function loginUser($conn, $uid, $pwd)
{
    $row = uidExists($conn, $uid);

    if ($row === false) {
        return false;
    }

    $pwdHashed = $row["userPwd"];
    $checkedPwd = password_verify($pwd, $pwdHashed);

    if ($checkedPwd === false) {
        return false;
    } 
    else {
        return true;
    }
}

function uploadImage($conn, $username, $image)
{
    if ($row = uidExists($conn, $username)) {
        $userId = $row["userId"];
        $sql = "INSERT INTO images (userId, code) VALUES (" . $userId . ", '" . $image . "');";
        if ($conn->query($sql) === TRUE) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

function getImageFromId($conn, $imgId)
{
    $sql = "SELECT code FROM images WHERE imageId = ?;";
    $stmt = mysqli_stmt_init($conn);
    if (!mysqli_stmt_prepare($stmt, $sql)) {
        return false;
    }
    mysqli_stmt_bind_param($stmt, "s", $imgId);
    mysqli_stmt_execute($stmt);
    $resultData = mysqli_stmt_get_result($stmt);

    if ($row = mysqli_fetch_assoc($resultData)) {
        mysqli_stmt_close($stmt);
        return $row["code"];
    } else {
        mysqli_stmt_close($stmt);
        return false;
    }
}

function checkCorrespondency($conn, $userId, $image)
{
    $sql = "SELECT * FROM images WHERE imageId = ?;";
    $stmt = mysqli_stmt_init($conn);
    if (!mysqli_stmt_prepare($stmt, $sql)) {
        return false;
    }
    mysqli_stmt_bind_param($stmt, "s", $image);
    mysqli_stmt_execute($stmt);
    $resultData = mysqli_stmt_get_result($stmt);

    if ($row = mysqli_fetch_assoc($resultData)) {
        mysqli_stmt_close($stmt);
        if($row["userID"] === $userId){
            return $row["code"];
        }
        else{
            return false;
        }
    } else {
        mysqli_stmt_close($stmt);
        return false;
    }
}