<?php

include_once "additional_pages/header.php";

if(isset($_SESSION['uid']) && isset($_POST['image']) && isset($_POST['submit'])){

    $username = $_SESSION['uid'];
    $imgId = $_POST["image"];

    require_once 'includes/db.access.php';
    require_once 'includes/functions.general.php';

    $row = uidExists($conn, $username);
    $userId = $row['userId'];

    if(checkCorrespondency($conn, $userId, $imgId)){
?>
    <div id="content">
    <div id="header">
        <form action="/explore.php" method="get">
            <div class="search-container">
                <input type="text" placeholder="Search..." name="uid" class="search-input" />
                <button type="submit" class="search-button">
                    <div class="search-button-container">
                        <i class="fas fa-search"></i>
                    </div>
                </button>
            </div>
        </form>
        <h1>
            <div id="username">Immagine eliminata!</div>
        </h1>
    </div>
    </div>
<?php
    }
    else{
        ?>
        <div id="content">
        <div id="header">
            <form action="/explore.php" method="get">
                <div class="search-container">
                    <input type="text" placeholder="Search..." name="uid" class="search-input" />
                    <button type="submit" class="search-button">
                        <div class="search-button-container">
                            <i class="fas fa-search"></i>
                        </div>
                    </button>
                </div>
            </form>
            <h1>
                <div id="username">Non puoi eliminare questa immagine!</div>
            </h1>
        </div>
        </div>
<?php
    }
}
else {
    //header("location: explore.php");
    exit();
}

include_once "additional_pages/footer.php"; ?>