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
    $dsinfo = $this->item->find_objects_by_pattern($this->item->pid, 'pid', 1, array('ownerId','state'));
    $this->extraInfo = $dsinfo[$this->item->pid];
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
    module_load_include('inc', 'adr_basic_viewer', 'ObjectViewDescription');
    $object_view = new ObjectViewDescription($this->item, $this->getContentModel());
    $description = $object_view->getDescription();
    $content = '';
    foreach ($description as $label => $value) {
      $value = filter_xss($value, array('a', 'br'));
      $content .= '<tr>';
      $content .= "<td style='padding: 5px; background:#cccccc; font-size: 1em; font-weight:bold; vertical-align:top;'>$label</td>";
            $content .= "<td style='padding:5px;font-size:1.2em; vertical-align: middle;'>$value</td>";
      $content .= '</tr>';
    }
    $created = $this->getObjectCreationDate();
    $modified = $this->getObjectLastModifiedDate();
    //$user = $this->getLastUserToModifyObject();
    // @TODO use classes instead of inlined values.
    $footer = "<tr><td><br/></td></tr>";
    $footer .= "<tr><td style='text-align: center;font-size:0.9em;'>";
    $footer .= "This object was added {$created}. ";
    $footer .= "This object was last updated {$modified}.</td></tr>";
    return "<table>{$content}</table><table>{$footer}</table>";
  }

  /**
   *
   * @return array
   */
  public function getDatastreams($start, $limit) {
    $data = array();
    $count = 0;
    $end = (isset($limit)) ? $start + $limit : NULL;
    foreach ($this->item->datastreams as $dsid => $attr) {
      if ($count >= $start && (empty($end) || $count < $end)) {
        module_load_include('inc', 'adr_basic_viewer', 'Thumbnail');
        $thumbnail = new Thumbnail($this->item, $dsid);
        $stream['dsid'] = $dsid;
        $stream['label'] = $attr['label'];
        $stream['img_url'] = $thumbnail->getUrl();
        $stream['download_url'] = $this->getDatastreamDownloadURL($dsid, $attr['label']);
        $stream['mime'] = $attr['MIMEType'];
        $data[] = $stream;
      }
      $count++;
    }
    return array("success" => TRUE, "data" => $data, "total" => $count);
  }

  /**
   *
   * @global string $base_url
   * @param string $dsid
   */
  private function getDatastreamDownloadURL($dsid, $label) {
    global $base_url;
    return "$base_url/fedora/repository/object_download/" . drupal_urlencode($this->pid) . '/' . $dsid . '/' . drupal_urlencode(preg_replace('/\//i', '${1}_', $label));
  }

  /**
   * Gets the fedora object's properties.
   *
   * @return array
   */
  public function getObjectProperties() {
    $object_properties = array(
      'pid' => $this->pid,
      'label' => $this->getObjectLabel(),
      'created' => $this->getObjectCreationDate(),
      'modified' => $this->getObjectLastModifiedDate(),
      'owner' => $this->getObjectOwner(),
      'state' => $this->getObjectState()
    );
    return array($object_properties);
  }

  /**
   * Sets the fedora object's properties.
   *
   * Input is expected to be from the form defined on the manage tab,
   * of the ADR Basic viewer.
   *
   * @return array
   *   Indicates the success of this function as well as the fedora
   *   objects current settings.
   */
  public function setObjectProperties($values) {
    $states = array(
      'Active' => 'A',
      'Inactive' => 'I',
      'Deleted' => 'D',
    );
    $label = $values['label'];
    $owner = $values['owner'];
    $state = $values['state'];
    if ($this->item->modify_object($label, $states[$state], $owner)) {
      $object_properties = $this->getObjectProperties();
      return array('success' => true, 'msg' => 'Successfully Edited Object', 'data' => $object_properties);
    }
    else {
      $object_properties = $this->getObjectProperties();
      return array('success' => false, 'msg' => 'Failed to Edit Object', 'data' => $object_properties);
    }
  }

  /**
   * Marks the fedora object in question as being deleted.
   *
   * @return array
   */
  public function deleteObject() {
    // mark the object as deleted in Fedora without purging the object
    $get_properties = $this->getObjectProperties();
    $object_properties = $get_properties[0];
    $object_properties['state'] = "Deleted";
    $set_properties = $this->setObjectProperties($object_properties);
    if ($set_properties['success']) {
      drupal_set_message("Successfully Deleted Object: {$this->pid}");
      return array('success' => true, 'msg' => 'Successfully Deleted Object');
    }
    else {
      return array('success' => false, 'msg' => 'Failed to Delete Object');
    }
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
    return $this->extraInfo['ownerId'];
  }

  /**
   * Gets the fedora object's current state.
   *
   * @return string
   */
  private function getObjectState() {
    return $this->extraInfo['state'];
  }

  /**
   *
   * @return array
   */
  public function getAllowedMIMETypes() {
    $content_model = &$this->getContentModel();
    $mime_types = $content_model->getMimetypes();
    $response = array();
    foreach ($mime_types as $type) {
      $response[] = array('mime' => $type);
    }
    return $response;
  }

  /**
   *
   * @param <type> $values
   * @return <type>
   */
  public function addDatastream($values) {
    $controls = array(
      'Inline XML (X)' => "X",
      'Managed Resource (M)' => "M",
      'Redirect (R)' => "R",
      'External Reference (E)' => "E",
    );
    $dsid = $values['dsid'];
    $label = $values['label'];
    $control = $controls[$values['control_group']];
    $mime = $values['mime_type'];
    $file = array_shift($_FILES);
    if ($file['type'] != $mime) {
      return array('success' => false, 'msg' => 'Mime type of file does not match the mime type specified.');
    }
    else {
      if ($this->item->add_datastream_from_file($file['tmp_name'], $dsid, $label, $mime, $control)) {
        return array('success' => true, 'msg' => 'Successfully added datastream.');
      }
      else {
        return array('success' => false, 'msg' => 'Failed to add datastream.');
      }
    }
  }

  /**
   * Deletes datastreams from the object.
   *
   * @param string $dsid
   * @return array
   */
  public function deleteDatastream($dsid) {
    if ($this->item->purge_datastream($dsid)) {
      return json_encode(array('success' => true, 'msg' => 'Successfully Deleted datastream.'));
    }
    else {
      return json_encode(array('success' => false, 'msg' => 'Failed to deleted file.'));
    }
  }

}
