(function () {
  farmOS.map.behaviors.farm_map_no = {
    attach: function (instance) {

      // Add Norkart Flyfoto layer.
      var opts = {
        title: 'Norkart Flyfoto',
        url: 'http://map04.eniro.no/geowebcache/service/tms1.0.0/aerial/{z}/{x}/{-y}.jpeg?c=2542211020&v=20160420',
        group: 'Base layers',
      };
      instance.addLayer('xyz', opts);
    },
  };
}());
