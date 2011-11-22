<?php

// $Id$

/**
 * @file
 *
 */

/**
 *
 */
class ADRCollection {

  /**
   * The pid of the collection this viewer will show.
   * @var string
   */
  protected $pid;
  /**
   * The path to this module.
   * 
   * @var string
   */
  protected $path;
  /**
   * The fedora object defined by $pid.
   * 
   * @var Fedora_Item 
   */
  protected $item;
  /**
   *
   * @var Collection
   */
  protected $collection;

  /**
   * Create the collection viewer.
   * 
   * @param string $pid
   *   The collection this viewer will show, if NULL is specified, the sites default top collection will
   *   be shown.
   */
  public function __construct($pid = NULL) {
    $this->pid = isset($pid) ? $pid : variable_get('fedora_repository_pid', 'islandora:top');
    module_load_include('inc', 'adr_collection_viewer', 'Collection');
    $this->collection = new Collection($this->pid);
    $this->path = drupal_get_path('module', 'adr_collection_viewer');
  }

  /**
   *
   */
  private function includeRequiredScripts() {
    $path = drupal_get_path('module', 'adr_collection_viewer');
    drupal_add_css("$path/stylesheets/Clear.css", 'theme', 'all');
    module_load_include('module', 'ext', 'ext');
    ext_load_library();
    drupal_add_css("$path/stylesheets/ADRCollection.css", 'theme', 'all');

    $data_stores = array(
      'Datastreams.js',
      'ControlGroups.js',
      'MIMETypes.js',
      'State.js',
      'CollectionProperties.js',
      'CollectionMembers.js'
    );

    $custom_components = array(
      'FileUploadField.ui.js',
      'FileUploadField.js',
      'EditObjectWindow.ui.js',
      'EditObjectWindow.js',
    );

    $main_viewer = array(
      'ADRCollectionViewer.ui.js',
      'ADRCollectionViewer.js',
      'Content.ui.js',
      'Content.js',
    );

    global $user; 
    module_load_include('inc', 'islandora_xacml_editor', 'Xacml');
    module_load_include('inc', 'islandora_xacml_editor', 'XacmlException');
    try {
      $xacml = Xacml::constructFromPid($this->pid);
      $canManageInXacml = $xacml->managementRule->hasPermission($user->name, $user->roles);
    }
    catch (XacmlException $e) {
      $canManageInXacml = FALSE;
    }

    $canAddNewObject = user_access("ingest new fedora objects") && $canManageInXacml;
    $canAddNewCollection = user_access("ingest new fedora objects") && $canManageInXacml;
    $canEditObjects = user_access("edit fedora meta data");
    $canEditPermissions = user_access("Edit XACML Policies");
    $canEditChildPermissions = user_access("Edit XACML Policies");
    $canAddStream = user_access("add fedora datastreams");
    $canDeleteObject = user_access("purge objects and datastreams");
    $canDeleteStream = user_access("purge objects and datastreams");
    $canEditStream = user_access("edit fedora meta data");

    $permissions_block =
        "UserCollectionPermissions.content_canAddNewObject=" . ($canAddNewObject ? "true" : "false") . ";" .
        "UserCollectionPermissions.content_canAddNewCollection=" . ($canAddNewCollection ? "true" : "false") . ";" .
        "UserCollectionPermissions.manage_canEditObjects=" . ($canEditObjects ? "true" : "false") . ";" .
        "UserCollectionPermissions.manage_canEditPermissions=" . ($canEditPermissions ? "true" : "false") . ";" .
        "UserCollectionPermissions.manage_canEditChildPermissions=" . ($canEditChildPermissions ? "true" : "false") . ";" .
        "UserCollectionPermissions.manage_canDeleteObject=" . ($canDeleteObject ? "true" : "false") . ";" .
        "UserCollectionPermissions.datastream_canAddStream=" . ($canAddStream ? "true" : "false") . ";" .
        "UserCollectionPermissions.datastream_canEditStream=" . ($canEditStream ? "true" : "false") . ";" .
        "UserCollectionPermissions.datastream_canDeleteStream=" . ($canDeleteStream ? "true" : "false") . ";";
    drupal_add_js($permissions_block, 'inline');
    
    drupal_add_js("$path/js/IncludeFirst.js");
    $title = $this->getCollectionTitle();
    $description = $this->getCollectionDescription();
    $js = "ADRCollection.title = \"$title\";\n";
    $js .= "ADRCollection.description = \"$description\";";
    drupal_add_js($js, 'inline');
    $this->includeScripts($data_stores, $path);
    $this->includeScripts($custom_components, $path);
    $this->includeScripts($main_viewer, $path);
    if ($this->canShowOverviewPanel()) {
      $this->includeOverviewPanel();
    }
    if ($this->canShowManagePanel()) {
      $this->includeManagePanel();
    }
    drupal_add_js("$path/js/ADRCollection.js");
    drupal_add_js("$path/js/resize.js");
  }

  /**
   * Can we show the overview panel.
   *
   * Checks to see if this object has a MODS datastream if so the overview panel can be included.
   *
   * @return boolean
   */
  private function canShowOverviewPanel() {
    return $this->collection->hasMetadata();
  }

  /**
   * Includes the required javascript to render the manage panel.
   */
  private function includeOverviewPanel() {
    drupal_add_js("{$this->path}/js/Overview.ui.js");
    drupal_add_js("{$this->path}/js/Overview.js");
  }

  /**
   * Can we show the manage panel.
   *
   * Checks user permissions to decide if the user can manage this collection.
   * 
   * @return boolean
   */
  private function canShowManagePanel() {
    module_load_include('inc','islandora_xacml_editor','Xacml');
    module_load_include('inc','islandora_xacml_editor','XacmlException');
    global $user;

    if ($user->uid == 1 || in_array('administrator', $user->roles)) {
      $show = TRUE;
    }
    else {
      try {
        $xacml = Xacml::constructFromPid($this->pid);
        if($xacml->managementRule->isPopulated()) {
          $show = $xacml->managementRule->hasPermission($user->name, $user->roles);
        }
        else {
          $show = FALSE;
        }
      }
      catch (XacmlException $e) {
        $show = FALSE;
      }
    }

    $show &= user_access('purge objects and datastreams')
    || user_access('add fedora datastreams')
    || user_access('edit fedora meta data');

    return $show;
  }

  /**
   * Includes the required javascript to render the manage panel.
   */
  private function includeManagePanel() {
    drupal_add_js("{$this->path}/js/Manage.ui.js");
    drupal_add_js("{$this->path}/js/Manage.js");
    drupal_add_js("{$this->path}/js/AddDatastream.ui.js");
    drupal_add_js("{$this->path}/js/AddDatastream.js");
  }

  /**
   *
   * @param array $scripts
   * @param string $path
   */
  private function includeScripts($scripts, $path) {
    foreach ($scripts as $file) {
      drupal_add_js("$path/js/$file");
    }
  }

  /**
   * Gets the html for this collections title.
   *
   * @return string
   */
  private function getCollectionTitle() {
    $label = $this->collection->getLabel();
    return "<h1 class='adr-collection-title'>{$label}</h1>";
  }

  /**
   * Gets the html for this collections description.
   *
   * @return string
   */
  private function getCollectionDescription() {
    $description = $this->collection->getDescription();
    $description = substr($description, 0, 350);
    if (isset($description) && trim($description) != '') {
      return "<table class='adr-collection-description'><tr><td class='adr-collection-description'>{$description}<a href='#adr-collection-title' id='adr-show-overview-link'> [Click for more ...]</a></td></tr></table>";
    }
    return NULL;
  }

  /**
   *
   */
  public function render() {
    $this->includeRequiredScripts(); // Javascript all the way!
  }

}
