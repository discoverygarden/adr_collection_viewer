<?php

// $Id$

/**
 * @file
 *
 */

/**
 * 
 */
class AjaxHandler {

  /**
   *
   * @var string
   */
  protected $pid;
  /**
   *
   * @var Fedora_Item
   */
  protected $item;
  /**
   * FOXML repersention of the Fedora Object identified by $pid.
   *
   * Access through the function AjaxHandler::getFoxmlDocument().
   * Do not access directly as it may not exist.
   *
   * @var DOMDocument
   */
  protected $foxml;
  /**
   * XPath for the FOXML document identified by $foxml.
   *
   * Access through the function AjaxHandler::getFoxmlXPath().
   * Do not directly as it may not exist.
   *
   * @var DOMDocument
   */
  protected $xpath;
  /**
   * This fedora objects content model.
   *
   * Access through the function AjaxHandler::getContentModel().
   * Do not directly as it may not exist.
   *
   * @var ContentModel
   */
  protected $contentModel;

  /**
   * 
   * @param string $pid
   */
  public function __construct($pid) {
    module_load_include('inc', 'fedora_repository', 'api/fedora_item');
    $this->pid = $pid;
    $this->item = new Fedora_Item($pid);
  }

  /**
   *
   *
   * @return ContentModel
   */
  private function &getContentModel() {
    if (empty($this->contentModel)) {
      module_load_include('inc', 'fedora_repository', 'ContentModel');
      $this->contentModel = ContentModel::loadFromObject($this->pid);
    }
    return $this->contentModel;
  }

  /**
   *
   * @return array
   */
  public function getDescription() {
    module_load_include('inc', 'adr_collection_viewer', 'ObjectViewDescription');
    $object_view = new ObjectViewDescription($this->item, $this->getContentModel());
    $description = $object_view->getDescription();
    $content = '';
    foreach ($description as $label => $value) {
      $content .= '<tr>';
      $content .= "<td style='padding:5px;font-size:1.5em;'>$label</td>";
      $content .= "<td style='padding:5px;font-size:1.2em;'>$value</td>";
      $content .= '</tr>';
    }
    $created = $this->getObjectCreationDate();
    $modified = $this->getObjectLastModifiedDate();
    $user = $this->getLastUserToModifyObject();
    // @TODO use classes instead of inlined values.
    $footer = "<tr><td colspan='2'><br/></td></tr>";
    $footer .= "<tr><td colspan='2' style='text-align: center;font-size:0.9em;'>";
    $footer .= "This object was added {$created}. ";
    $footer .= "This object was last updated {$modified} by {$user}.</td></tr>";
    return "<table width='100%'>{$content}{$footer}</table>";
  }

  /**
   * Gets the fedora object's label.
   *
   * @return string
   */
  private function getObjectLabel() {
    return $this->item->objectProfile->objLabel;
  }

  /**
   * Gets the fedora object's creation date in the format "Month Day, Year".
   *
   * @return string
   */
  private function getObjectCreationDate() {
    $date_created = new DateTime($this->item->objectProfile->objCreateDate);
    return $date_created->format('F j, Y');
  }

  /**
   * Gets the fedora object's last modified date in the format "Month Day, Year".
   *
   * @return string
   */
  private function getObjectLastModifiedDate() {
    $date_modified = new DateTime($this->item->objectProfile->objLastModDate);
    return $date_modified->format('F j, Y');
  }

  /**
   * Gets the fedora object's owner id.
   *
   * @return string
   */
  private function getObjectOwner() {
    $xpath = $this->getFoxmlXPath();
    $result = $xpath->query("/foxml:digitalObject/foxml:objectProperties/foxml:property[@NAME='info:fedora/fedora-system:def/model#ownerId']/@VALUE");
    if ($result && $result->length == 1) {
      return $result->item(0)->value;
    }
    return '';
  }

  /**
   * Gets the fedora object's current state.
   *
   * @return string
   */
  private function getObjectState() {
    $xpath = $this->getFoxmlXPath();
    $result = $xpath->query("/foxml:digitalObject/foxml:objectProperties/foxml:property[@NAME='info:fedora/fedora-system:def/model#state']/@VALUE");
    if ($result && $result->length == 1) {
      return $result->item(0)->value;
    }
    return '';
  }

  /**
   *
   */
  private function getLastUserToModifyObject() {
    $xpath = $this->getFoxmlXPath();
    $result = $xpath->query("(//*[local-name()='responsibility'])[last()]");
    $audit = $result->item(0)->nodeValue;
    return sprintf("%s", $audit);
  }

  /**
   * Gets this objects FOXML repersentation, as a DOMDocument.
   *
   * Creates a new DOMDocument object from this objects exported FOXML, storing it
   * as a member if it doesn't already exist.
   *
   * @return DOMDocument
   */
  private function getFoxmlDocument() {
    if (empty($this->foxml)) {
      $foxml = $this->item->export_as_foxml();
      $this->foxml = new DOMDocument();
      $this->foxml->loadXML($foxml);
      return $this->foxml;
    }
    else {
      return $this->foxml;
    }
  }

  /**
   * Get the XPath for this object FOXML repersentation.
   *
   * Creates a new DOMXPath object, storing it as a member if it doesn't already exist.
   *
   * @return DOMXPath
   *   XPath for this object FOXML repersentation.
   */
  private function getFoxmlXPath() {
    if (empty($this->xpath)) {
      $foxml = $this->getFoxmlDocument();
      $this->xpath = new DOMXPath($foxml);
      $this->registerFoxmlNamespaces($foxml->saveXML());
      return $this->xpath;
    }
    else {
      return $this->xpath;
    }
  }

  /**
   * Registers all namespaces found in the foxml document.
   *
   * @param string $foxml
   *   XML string of the exported fedora objects foxml.
   */
  private function registerFoxmlNamespaces($foxml) {
    $simple = new SimpleXMLElement($foxml);
    $names = $simple->getNamespaces(TRUE);
    foreach ($names as $prefix => $uri) {
      $this->xpath->registerNamespace($prefix, $uri);
    }
  }

}