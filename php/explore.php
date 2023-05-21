<?php
include_once "additional_pages/header.php";
include_once 'includes/get_images.php';
?>

<body>
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
            <?php
            if ($showHub) {
                echo '
                    <h1>
                    <div id="hub">
                        Hub della comunità
                    </div>
                    </h1>';
            } else if ($showUser === false) {
                echo '<h1><div id="username">Utente non trovato</div></h1>';
            } else {
                echo '<h1><div id="username">' . $username . '</div></h1>';
            }
            ?>
        </div>
        <div id="images">
            <?php if ($showUser !== false)
                foreach ($imageList as $image): ?>
                    <div class="image-container">
                        <div class="image-wrapper">
                            <?php
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
                                        ob_start();
                                        imagepng(drawImage($image['code']));
                                        $lightboxImage = base64_encode(ob_get_clean());
                                        echo '<img src="data:image/png;base64,' . $lightboxImage . '" style="image-rendering: pixelated;" />';
                                        imagedestroy(drawImage($image['code']));
                                    ?>
                                </div>
                                <div class="lightbox-buttons">
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