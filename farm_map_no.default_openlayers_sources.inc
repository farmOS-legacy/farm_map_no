<?php
/**
 * @file
 * farm_map_no.default_openlayers_sources.inc
 */

/**
 * Implements hook_default_openlayers_sources().
 */
function farm_map_no_default_openlayers_sources() {
  $export = array();

  // Load the Kartverket WMTS URL.
  $url = farm_map_no_kartverket_wmts();

  // Load the Kartverket layer names.
  $layers = farm_map_no_kartverket_wmts_layers();

  // Generate a source for each layer.
  foreach ($layers as $layer => $name) {

    $ol_source = new stdClass();
		$ol_source->disabled = FALSE; /* Edit this to true to make a default ol_source disabled initially */
		$ol_source->api_version = 1;
		$ol_source->machine_name = 'farm_map_no_source_kartverket' . $layer;
		$ol_source->name = 'Farm Map Norway: Kartverket ' . $name;
		$ol_source->description = '';
		$ol_source->factory_service = 'openlayers.Source:InlineJS';
		$ol_source->options = array(
		  'javascript' => '

// Code adapted from https://github.com/kartverket/example-clients/blob/master/openlayers3/wmts_mercator.html

//Start: projection & tileGrid definitions
var sProjection = "EPSG:3857";
var projection = ol.proj.get(sProjection);
var projectionExtent = projection.getExtent();
var size = ol.extent.getWidth(projectionExtent) / 256;
var resolutions = [],
	matrixIds = [];
for (var z = 0; z < 15; ++z) { //Max 18?
	// generate resolutions and matrixIds arrays for this WMTS
	resolutions[z] = size / Math.pow(2, z);
	matrixIds[z] = sProjection + ":" + z;
}
//End: projection & tileGrid definitions
//start View definitions
var view = new ol.View({
	projection: sProjection,
	center: [1891337, 9772319],
	zoom: 5
});
//End View definitions
//Start: Map definitions
var map = new ol.Map({
	target: "map",
	view: view
});
//End: Map definitions
//***********************
var _url = "' . $url . '?";
//Start: source
var source = new ol.source.WMTS({
	url: _url,
	layer: "' . $layer . '",
	matrixSet: "EPSG:3857",
	format: "image/png",
	projection: projection,
	tileGrid: new ol.tilegrid.WMTS({
		origin: ol.extent.getTopLeft(projectionExtent),
		resolutions: resolutions,
		matrixIds: matrixIds
	}),
	style: "default"
});
//End: source

',
		);
		$export['farm_map_no_source_kartverket_' . $layer] = $ol_source;
  }

  // Generate a Norkart Flyfoto source.
  $ol_source = new stdClass();
  $ol_source->disabled = FALSE; /* Edit this to true to make a default ol_source disabled initially */
  $ol_source->api_version = 1;
  $ol_source->machine_name = 'farm_map_no_source_norkart_flyfoto';
  $ol_source->name = 'Farm Map Norway: Norkart Flyfoto';
  $ol_source->description = '';
  $ol_source->factory_service = 'openlayers.Source:XYZ';
  $ol_source->options = array(
    'url' => 'http://map04.eniro.no/geowebcache/service/tms1.0.0/aerial/{z}/{x}/{-y}.jpeg?c=2542211020&v=20160420',
  );
  $export['farm_map_no_source_norkart_flyfoto'] = $ol_source;

  return $export;
}
