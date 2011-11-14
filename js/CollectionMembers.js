/*
 * File: CollectionMembers.js
 * Date: Fri Nov 11 2011 18:52:39 GMT-0400 (AST)
 * 
 * This file was generated by Ext Designer version 1.1.2.
 * http://www.sencha.com/products/designer/
 *
 * This file will be auto-generated each and everytime you export.
 *
 * Do NOT hand edit this file.
 */

CollectionMembers = Ext.extend(Ext.data.JsonStore, {
    constructor: function(cfg) {
        cfg = cfg || {};
        CollectionMembers.superclass.constructor.call(this, Ext.apply({
            storeId: 'CollectionMembers',
            url: '/adrcollection/ajax/getCollectionMembers',
            root: 'data',
            baseParams: {
                pid: decodeURIComponent(window.location.pathname.split('/')[
                    3
                ])
            },
            fields: [
                {
                    name: 'title'
                },
                {
                    name: 'pid'
                },
                {
                    name: 'description'
                },
                {
                    name: 'url'
                },
                {
                    name: 'img_url'
                }
            ]
        }, cfg));
    }
});
new CollectionMembers();