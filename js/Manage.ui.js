/*
 * File: Manage.ui.js
 * Date: Fri Apr 08 2011 13:32:20 GMT-0300 (ADT)
 * 
 * This file was generated by Ext Designer version 1.1.2.
 * http://www.sencha.com/products/designer/
 *
 * This file will be auto-generated each and everytime you export.
 *
 * Do NOT hand edit this file.
 */

ManageUi = Ext.extend(Ext.Panel, {
    title: 'Manage',
    initComponent: function() {
        this.items = [
            {
                xtype: 'panel',
                title: 'Collection Properties',
                frame: true,
                fbar: {
                    xtype: 'toolbar',
                    items: [
                        {
                            xtype: 'button',
                            text: 'Edit Metadata'
                        },
                        {
                            xtype: 'button',
                            text: 'Edit Permissions'
                        },
                        {
                            xtype: 'button',
                            text: 'Delete Collection'
                        }
                    ]
                }
            },
            {
                xtype: 'panel',
                title: 'Manage Collection Datastreams',
                footer: true,
                layout: 'border',
                tbar: {
                    xtype: 'toolbar'
                },
                items: [
                    {
                        xtype: 'listview',
                        columnResize: false,
                        store: 'Datastreams',
                        region: 'center',
                        columns: [
                            {
                                xtype: 'lvcolumn',
                                header: 'Label',
                                width: 0.25,
                                dataIndex: 'label'
                            },
                            {
                                xtype: 'lvcolumn',
                                header: 'Datastream ID',
                                dataIndex: 'dsid'
                            },
                            {
                                xtype: 'lvcolumn',
                                header: 'Mime Type',
                                dataIndex: 'mime'
                            }
                        ]
                    },
                    {
                        xtype: 'panel',
                        title: 'Detailed Information',
                        region: 'west',
                        width: 100,
                        html: 'Select a Datastream'
                    }
                ],
                bbar: {
                    xtype: 'paging',
                    store: 'Datastreams'
                }
            }
        ];
        ManageUi.superclass.initComponent.call(this);
    }
});