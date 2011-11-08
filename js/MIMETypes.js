/*
 * File: MIMETypes.js
 * Date: Tue Nov 08 2011 16:20:39 GMT-0400 (AST)
 * 
 * This file was generated by Ext Designer version 1.1.2.
 * http://www.sencha.com/products/designer/
 *
 * This file will be auto-generated each and everytime you export.
 *
 * Do NOT hand edit this file.
 */

MIMETypes = Ext.extend(Ext.data.JsonStore, {
    constructor: function(cfg) {
        cfg = cfg || {};
        MIMETypes.superclass.constructor.call(this, Ext.apply({
            storeId: 'MIMETypes',
            url: '/adrcollection/ajax/getAllowedMIMETypes',
            autoLoad: true,
            baseParams: {
                pid: decodeURIComponent(window.location.pathname.split('/')[
                    3
                ])
            },
            fields: [
                {
                    name: 'mime'
                }
            ]
        }, cfg));
    }
});
new MIMETypes();