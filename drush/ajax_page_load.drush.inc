<?php

/**
 * @file
 * Drush integration for NProgress library.
 */

/**
 * The NProgress plugin URI.
 */
define('AJAX_PAGE_LOAD_NPROGRESS_DOWNLOAD_URI', 'https://github.com/rstacruz/nprogress/archive/master.zip');
define('AJAX_PAGE_LOAD_NPROGRESS_DOWNLOAD_PREFIX', 'nprogress-');

/**
 * Implements hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * See `drush topic docs-commands` for a list of recognized keys.
 */
function ajax_page_load_drush_command() {
  $items = array();

  // The key in the $items array is the name of the command.
  $items['nprogress-plugin'] = array(
    'callback' => 'drush_ajax_page_load_nprogress_plugin',
    'description' => dt('Download and install the NProgress plugin.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(),
    'aliases' => array('nprogressplugin'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function ajax_page_load_drush_help($section) {
  switch ($section) {
    case 'drush:nprogress-plugin':
      return dt('Download and install the NProgress plugin from ricostacruz.com/nprogress, default location is sites/all/libraries.');
  }
}

/**
 * Command to download the NProgress plugin.
 */
function drush_ajax_page_load_nprogress_plugin() {
  $path = 'sites/all/libraries';

  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }

  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);

  // Download the zip archive.
  if ($filepath = drush_download_file(AJAX_PAGE_LOAD_NPROGRESS_DOWNLOAD_URI)) {
    $filename = basename($filepath);
    $dirname = AJAX_PAGE_LOAD_NPROGRESS_DOWNLOAD_PREFIX . basename($filepath, '.zip');

    // Remove any existing NProgress plugin directory.
    if (is_dir($dirname) || is_dir('nprogress')) {
      drush_delete_dir($dirname, TRUE);
      drush_delete_dir('nprogress', TRUE);
      drush_log(dt('A existing nprogress plugin was deleted from @path', array('@path' => $path)), 'notice');
    }

    // Decompress the zip archive.
    drush_tarball_extract($filename);

    // Change the directory name to "nprogress" if needed.
    if ($dirname != 'nprogress') {
      drush_move_dir($dirname, 'nprogress', TRUE);
      $dirname = 'nprogress';
    }
  }

  if (is_dir($dirname)) {
    drush_log(dt('NProgress plugin has been installed in @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the NProgress plugin to @path', array('@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);
}
