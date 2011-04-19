/*
 * File: EditObjectWindow.ui.js
 * Date: Tue Apr 19 2011 20:11:58 GMT-0300 (ADT)
 * 
 * This file was generated by Ext Designer version 1.1.2.
 * http://www.sencha.com/products/designer/
 *
 * This file will be auto-generated each and everytime you export.
 *
 * Do NOT hand edit this file.
 */

EditObjectWindowUi = Ext.extend(Ext.Window, {
    title: 'Edit Object',
    width: 542,
    height: 164,
    layout: 'fit',
    cls: 'adr-clear',
    id: 'adr-edit-obj-window',
    initComponent: function() {
        this.items = [
            {
                xtype: 'form',
                headerAsText: false,
                frame: true,
                items: [
                    {
                        xtype: 'textfield',
                        fieldLabel: 'Label',
                        anchor: '100%',
                        name: 'label'
                    },
                    {
                        xtype: 'textfield',
                        fieldLabel: 'Owner',
                        anchor: '100%',
                        name: 'owner'
                    },
                    {
                        xtype: 'combo',
                        fieldLabel: 'State',
                        anchor: '100%',
                        store: 'State',
                        mode: 'local',
                        allowBlank: false,
                        name: 'state',
                        displayField: 'type',
                        valueField: 'value',
                        submitValue: true,
                        editable: false,
                        triggerAction: 'all',
                        forceSelection: true
                    }
                ],
                fbar: {
                    xtype: 'toolbar',
                    items: [
                        {
                            xtype: 'button',
                            text: 'Save'
                        }
                    ]
                }
            }
        ];
        EditObjectWindowUi.superclass.initComponent.call(this);
    }
});
