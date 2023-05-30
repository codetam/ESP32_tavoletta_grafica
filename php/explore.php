<?php
include_once "additional_pages/header.php";
/* Viene incluso il file associato ai record delle immagini */
include_once 'includes/get_images.php';
?>

<body>
    <div id="content">
        <div id="header">   
            <?php
            include_once "additional_pages/search.php";
            if ($showHub) {                     // Non è stata mandata nessuna GET
                echo '
                    <h1>
                    <div id="hub">
                        Hub della comunità
                    </div>
                    </h1>';
            } else if ($showUser === false) {   // L'utente cercato non è riconosciuto
                echo '<h1><div id="general">Utente non trovato</div></h1>';
            } else {                            // L'utente cercato è riconosciuto
                echo '<h1><div id="general">' . $username . '</div></h1>';
            }
            ?>
        </div>
        <div id="images">
            <?php if ($showHub === true || $showUser === true)
                foreach ($imageList as $image): ?>
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
                                <div class="lightbox-buttons">
                                    <?php 
                                        echo '<h1><div class="lightbox-text">' . getUsernameFromUid($conn, $image['userID']) . '</div></h1>';
                                    ?>
                                    <!-- Codice per il button Carica -->
                                    <form action="load_id_to_esp.php" method="post">
                                        <button type="submit" name="submit" class="load-button">Carica</button>
                                        <?php echo '<input type="hidden" name="image" value="' . $image['imageId'] . '">' ?>
                                    </form>
                                </div>
                            </div>
                        </div>
                    </div>
                <?php endforeach; ?>
        </div>
    </div>
</body>

<?php include_once "additional_pages/footer.php"; ?>