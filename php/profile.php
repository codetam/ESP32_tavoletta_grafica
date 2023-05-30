<?php
include_once "additional_pages/header.php";
?>

<div id="content">
    <div id="header">
        <?php
        include_once "additional_pages/search.php";
        if (isset($_SESSION["uid"])) { // Controlla che la SESSION sia stata avviata (l'utente è loggato)

            require_once 'includes/db.access.php';
            require_once 'includes/functions.general.php';
            require_once 'includes/functions.image.php';

            $username = $_SESSION["uid"];
            $userRow = uidExists($conn, $username);
            $imageList = getUserImages($conn, $userRow['userId']);

            ?>
            <h1>
                <div id="general">
                    <?php echo $username; ?>
                </div>
            </h1>
        </div>
        <div id="images">
            <?php foreach ($imageList as $image): ?>
                <div class="image-container">
                <div class="image-wrapper">
                            <?php
                            /* Viene stampata l'immagine su schermo */
                            ob_start();
                            imagepng(drawImage($image['code']));
                            $base64Image = base64_encode(ob_get_clean());
                            echo '<img src="data:image/png;base64,' . $base64Image . '" style="image-rendering: pixelated;" />';
                            imagedestroy(drawImage($image['code']));
                            ?>
                        </div>
                    <div class="lightbox-overlay">
                            <div class="lightbox-content">
                                <div class="lightbox-image">
                                    <?php
                                        /* Codice per il lightbox */
                                        ob_start();
                                        imagepng(drawImage($image['code']));
                                        $lightboxImage = base64_encode(ob_get_clean());
                                        echo '<img src="data:image/png;base64,' . $lightboxImage . '" style="image-rendering: pixelated;" />';
                                        imagedestroy(drawImage($image['code']));
                                    ?>
                                </div>
                                <div class="lightbox-profile-buttons">
                                    <!-- Codice per i button Carica e Elimina -->
                                    <form action="delete_image.php" method="post">
                                        <button type="submit" name="submit" class="profile-delete-button">Elimina</button>
                                        <?php echo '<input type="hidden" name="image" value="' . $image['imageId'] . '">' ?>
                                    </form>
                                    <form action="load_id_to_esp.php" method="post">
                                        <button type="submit" name="submit" class="profile-load-button">Carica</button>
                                        <?php echo '<input type="hidden" name="image" value="' . $image['imageId'] . '">' ?>
                                    </form>
                                </div>
                            </div>
                        </div>
                </div>
            <?php endforeach; ?>
        </div>
    </div>
<?php 
    } 
    else { 
?>
    <h1>
        <div id="general">Devi essere loggato per visualizzare questa pagina!</div>
    </h1>
    </div>
</div>
<?php 
    }
    include_once "additional_pages/footer.php"; ?>