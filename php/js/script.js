/* JS per il lightbox */
$(document).ready(function () {
    $('.image-wrapper').click(function () {
        $(this).next('.lightbox-overlay').fadeIn();
    });

    $('.lightbox-overlay').click(function (e) {
        if ($(e.target).hasClass('lightbox-overlay')) {
            $(this).fadeOut();
        }
    });
});
