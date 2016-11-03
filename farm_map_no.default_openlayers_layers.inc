<?php
/**
 * @file
 * farm_map_no.default_openlayers_layers.inc
 */

/**
 * Implements hook_default_openlayers_layers().
 */
function farm_map_no_default_openlayers_layers() {
  $export = array();

  // Load the Kartverket layer names.
  $layers = farm_map_no_kartverket_wmts_layers();

  // Generate a layer for each.
  foreach ($layers as $layer => $name) {
		$ol_layer = new stdClass();
		$ol_layer->disabled = FALSE; /* Edit this to true to make a default ol_layer disabled initially */
		$ol_layer->api_version = 1;
		$ol_layer->machine_name = 'farm_map_no_layer_kartverket_' . $layer;
		$ol_layer->name = 'Kartverket: ' . $name;
		$ol_layer->description = '';
		$ol_layer->factory_service = 'openlayers.Layer:Tile';
		$ol_layer->options = array(
		  'source' => 'farm_map_no_source_kartverket' . $layer,
		  'visible' => 1,
		  'opacity' => 1,
		);
		$export['farm_map_no_layer_kartverket_' . $layer] = $ol_layer;
  }

  return $export;
}

/**
 * Implements hook_default_openlayers_layers_alter().
 */
function farm_map_no_default_openlayers_layers_alter(&$layers) {

  // Add Kartverket layers to farm_map_layer_group.
  if (!empty($layers['farm_map_layer_group'])) {

    // Load the Kartverket layer names.
    $kartverket_layers = farm_map_no_kartverket_wmts_layers();

    // Create a list of Openlayers layer names.
    $kartverket_ol_layers = array();
    foreach ($kartverket_layers as $layer => $name) {
      $kartverket_ol_layers[] = 'farm_map_no_layer_kartverket_' . $layer;
    }

    // Merge into existing layers.
    $existing_layers = $layers['farm_map_layer_group']->options['grouplayers'];
    $layers['farm_map_layer_group']->options['grouplayers'] = array_merge($kartverket_ol_layers, $existing_layers);
  }
}

