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
   * Create the collection viewer.
   * 
   * @param string $pid
   *   The collection this viewer will show, if NULL is specified, the sites default top collection will
   *   be shown.
   */
  public function __construct($pid = NULL) {
    $this->pid = isset($pid) ? $pid : variable_get('fedora_repository_pid', 'islandora:top');
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
    );

    $custom_components = array(
    );

    $main_viewer = array(
      'ADRCollectionViewer.ui.js',
      'ADRCollectionViewer.js',
      'Content.ui.js',
      'Content.js',
    );

    drupal_add_js("$path/js/IncludeFirst.js");
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
  }

  /**
   * Can we show the overview panel.
   *
   * Checks to see if this object has a MODS datastream if so the overview panel can be included.
   *
   * @return boolean
   */
  private function canShowOverviewPanel() {
    return isset($this->item->datastreams['MODS']);
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
    return user_access('purge objects and datastreams')
    && user_access('add fedora datastreams')
    && user_access('edit fedora meta data');
  }

  /**
   * Includes the required javascript to render the manage panel.
   */
  private function includeManagePanel() {
    drupal_add_js("{$this->path}/js/Manage.ui.js");
    drupal_add_js("{$this->path}/js/Manage.js");
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
   *
   */
  public function render() {
    $this->includeRequiredScripts(); // Javascript all the way!
    return "<div id='content-fedora'></div>";
  }

}