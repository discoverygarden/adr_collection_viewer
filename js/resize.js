/*
var maxSize=32;

$('.adr-content-item-icon img').live('onChange', function () {
    alert(this);

    var height =$(this).height();
    var width = $(this).width();
    if (height > width)
    {
        if ( height > maxSize) 
        {
            $(this).height(maxSize);
            $(this).width( maxSize*width/height );
        }

    }
    else{
        if (width > maxSize)
        {
            $(this).width(maxSize);
            $(this).height(maxSize*height/width);
            $(this).css('margin-top',  (maxSize-$(this).height())/2+'px');
        }

    }
});
*/

function resizeImage(e, maxSize) {

    var height = $(e).height();
    var width = $(e).width();
    if (height > width)
    {
        if ( height > maxSize)
        {
            $(e).height(maxSize);
            $(e).width( maxSize*width/height );
        }

    }
    else{
        if (width > maxSize)
        {
            $(e).width(maxSize);
            $(e).height(maxSize*height/width);
            $(e).css('margin-top',  (maxSize-$(e).height())/2+'px');
        }

    }
}