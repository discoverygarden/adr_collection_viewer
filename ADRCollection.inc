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
   *
   * @var string
   */
  protected $pid;

  /**
   *
   * @param string $pid 
   */
  public function __construct($pid) {
    $this->pid;
  }

  /**
   *
   */
  private function includeRequiredScripts() {
    $path = drupal_get_path('module', 'adr_collection_viewer');
    module_load_include('module', 'ext', 'ext');
    ext_load_library();
    drupal_add_css("$path/stylesheets/ADRCollection.css", 'theme', 'all');
    module_load_include('inc', 'adr_basic_viewer', 'ADRBasicViewer');
    ADRBasicViewer::includeRequiredJSForViewers($this->pid);

    $data_stores = array(
    );

    $custom_components = array(
    );

    $main_viewer = array(
    );

    drupal_add_js("$path/js/IncludeFirst.js");
    $this->includeScripts($data_stores, $path);
    $this->includeScripts($custom_components, $path);
    $this->includeScripts($main_viewer, $path);
    /*if(user_access('purge objects and datastreams') && user_access('add fedora datastreams') && user_access('edit fedora meta data')) {
      $this->includeScripts($manage_panel, $path);
      $this->includeScripts($manage_windows, $path);
    }*/
    drupal_add_js("$path/js/ADRCollection.js");
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
  }

}