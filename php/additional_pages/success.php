<?php
include_once "header.php";
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
            <div id="general">Immagine caricata con successo!</div>
        </h1>
    </div>
</div>

<?php include_once "footer.php"; ?>