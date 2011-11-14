/*
 * File: AddDatastream.ui.js
 * Date: Fri Nov 11 2011 18:52:39 GMT-0400 (AST)
 * 
 * This file was generated by Ext Designer version 1.1.2.
 * http://www.sencha.com/products/designer/
 *
 * This file will be auto-generated each and everytime you export.
 *
 * Do NOT hand edit this file.
 */

AddDatastreamUi = Ext.extend(Ext.Window, {
    title: 'My Window',
    width: 600,
    height: 250,
    padding: '10px',
    autoHeight: true,
    initComponent: function() {
        this.items = [
            {
                xtype: 'form',
                unstyled: true,
                fileUpload: true,
                items: [
                    {
                        xtype: 'textfield',
                        name: 'dsid',
                        allowBlank: false,
                        fieldLabel: 'Datastream ID'
                    },
                    {
                        xtype: 'textfield',
                        fieldLabel: 'Label',
                        anchor: '100%',
                        name: 'label',
                        allowBlank: false
                    },
                    {
                        xtype: 'combo',
                        fieldLabel: 'Control Group',
                        anchor: '100%',
                        name: 'control_group',
                        store: 'ControlGroups',
                        allowBlank: false,
                        displayField: 'type',
                        mode: 'local',
                        forceSelection: true,
                        editable: false,
                        triggerAction: 'all',
                        valueField: 'value',
                        submitValue: true
                    },
                    {
                        xtype: 'combo',
                        fieldLabel: 'MIME Type',
                        anchor: '100%',
                        name: 'mime_type',
                        store: 'MIMETypes',
                        allowBlank: false,
                        forceSelection: true,
                        triggerAction: 'all',
                        displayField: 'mime',
                        editable: false
                    },
                    {
                        fieldLabel: 'Upload File',
                        xtype: 'fileuploadfield'
                    }
                ],
                fbar: {
                    xtype: 'toolbar',
                    items: [
                        {
                            xtype: 'button',
                            text: 'Add'
                        }
                    ]
                }
            }
        ];
        AddDatastreamUi.superclass.initComponent.call(this);
    }
});
