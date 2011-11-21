/*
 * File: ControlGroups.js
 * Date: Mon Nov 21 2011 14:45:01 GMT-0400 (AST)
 * 
 * This file was generated by Ext Designer version 1.1.2.
 * http://www.sencha.com/products/designer/
 *
 * This file will be auto-generated each and everytime you export.
 *
 * Do NOT hand edit this file.
 */

ControlGroups = Ext.extend(Ext.data.ArrayStore, {
    constructor: function(cfg) {
        cfg = cfg || {};
        ControlGroups.superclass.constructor.call(this, Ext.apply({
            storeId: 'ControlGroups',
            autoLoad: true,
            data: [
                [
                    "Inline XML (X)",
                    "X"
                ],
                [
                    "Managed Resource (M)",
                    "M"
                ],
                [
                    "Redirect (R)",
                    "R"
                ],
                [
                    "External Reference (E)",
                    "E"
                ]
            ],
            fields: [
                {
                    name: 'type'
                },
                {
                    name: 'value'
                }
            ]
        }, cfg));
    }
});
new ControlGroups();