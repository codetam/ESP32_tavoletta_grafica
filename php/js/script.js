
$(document).ready(function () {
    $('.image-wrapper').click(function () {
        $(this).next('.lightbox-overlay').fadeIn();
    });

    $('.lightbox-overlay').click(function (e) {
        if ($(e.target).hasClass('lightbox-overlay')) {
            $(this).fadeOut();
        }
    });

    $('.delete-button').click(function () {
        // Handle delete functionality here
        // You can use AJAX to send a request to delete the image
    });

    $('.load-button').click(function () {
        // Handle load functionality here
        // You can redirect the user to another page or perform an action
    });
});
