/*
 * File: Overview.ui.js
 * Date: Tue Apr 19 2011 14:24:38 GMT-0300 (ADT)
 * 
 * This file was generated by Ext Designer version 1.1.2.
 * http://www.sencha.com/products/designer/
 *
 * This file will be auto-generated each and everytime you export.
 *
 * Do NOT hand edit this file.
 */

OverviewUi = Ext.extend(Ext.Panel, {
    title: 'Overview',
    autoHeight: true,
    id: 'adr-collection-overview-tab',
    initComponent: function() {
        this.items = [
            {
                xtype: 'panel',
                title: 'Description',
                autoLoad: {
                    url: "/adrcollection/ajax/getdescription",
                    params: {
                        pid: (window.location.pathname.split('/')[
                            3
                        ])
                    }
                },
                autoHeight: true,
                frame: true
            }
        ];
        OverviewUi.superclass.initComponent.call(this);
    }
});
