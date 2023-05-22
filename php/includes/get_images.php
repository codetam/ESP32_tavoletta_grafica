<?php
    require_once 'includes/db.access.php';
    require_once 'includes/functions.general.php';
    require_once 'includes/functions.image.php';


/* 
   Ritorna i record associati all'utente se è stata mandata 
   una richiesta GET con il parametro 'UID'. 
   Altrimenti ritorna tutti i record nella tabella delle immagini
*/
if( isset($_GET['uid']) ) {
    $showHub = false;
    $imageList;

    $username = $_GET["uid"];
    $userRow = uidExists($conn, $username);

    if(sizeof($userRow) == 0){  // Non esiste nessun utente con l'UID selezionato
        $showUser = false;
    }
    else{
        $showUser = true;
        $imageList = getUserImages($conn, $userRow['userId']);
    }
}
else {
    $showUser = false;
    $showHub = true;
    $username = "";
    $imageList = getAllImages($conn);
}