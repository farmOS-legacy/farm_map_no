<?php
/**
 * @file
 * farm_map_kartverket.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function farm_map_kartverket_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "openlayers" && $api == "default_openlayers_layers") {
    return array("version" => "1");
  }
  if ($module == "openlayers" && $api == "default_openlayers_sources") {
    return array("version" => "1");
  }
}
