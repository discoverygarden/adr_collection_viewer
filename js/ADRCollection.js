/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

// Create the viewer.
Ext.onReady(function(){
    Ext.get('tabs-tabset').update(ADRCollection.title + ADRCollection.description);
    Ext.get('tabs-tabset').dom.id = "adr-collection-viewer";
    Ext.QuickTips.init();
    new ADRCollectionViewer({
        renderTo: 'adr-collection-viewer'
    }).show();
});