/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

// Create the viewer.
Ext.onReady(function(){

    Ext.get('content-fedora').update('');
    Ext.get('content-fedora').dom.id = "adr-collection-viewer";
    Ext.QuickTips.init();
});