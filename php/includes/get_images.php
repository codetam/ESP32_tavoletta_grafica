<?php
    require_once 'includes/db.access.php';
    require_once 'includes/functions.general.php';
    require_once 'includes/functions.image.php';

$showUser = true;

if( isset($_GET['uid']) ) {
    $showHub = false;
    $imageList;

    $username = $_GET["uid"];
    $userRow = uidExists($conn, $username);

    if( $userRow === false){
        $showUser = false;
    }
    else{
        $imageList = getUserImages($conn, $userRow['userId']);
    }
}
else {
    $showHub = true;
    $username = "";
    $imageList = getAllImages($conn);
}