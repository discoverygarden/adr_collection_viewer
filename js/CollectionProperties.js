/*
 * File: CollectionProperties.js
 * Date: Mon Nov 21 2011 14:45:01 GMT-0400 (AST)
 * 
 * This file was generated by Ext Designer version 1.1.2.
 * http://www.sencha.com/products/designer/
 *
 * This file will be auto-generated each and everytime you export.
 *
 * Do NOT hand edit this file.
 */

CollectionProperties = Ext.extend(Ext.data.JsonStore, {
    constructor: function(cfg) {
        cfg = cfg || {};
        CollectionProperties.superclass.constructor.call(this, Ext.apply({
            storeId: 'ObjectProperties',
            url: '/adrcollection/ajax/getObjectProperties',
            autoLoad: true,
            baseParams: {
                pid: decodeURIComponent(window.location.pathname.split('/')[
                    3
                ])
            },
            fields: [
                {
                    name: 'label'
                },
                {
                    name: 'created'
                },
                {
                    name: 'modified'
                },
                {
                    name: 'owner'
                },
                {
                    name: 'state'
                },
                {
                    name: 'user'
                }
            ]
        }, cfg));
    }
});
new CollectionProperties();