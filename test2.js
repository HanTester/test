{ "type": "FeatureCollection",
    "features": [
      { "type": "Feature",
        "geometry": {"type": "AAAA", "coordinates": [102.0, 'aa']},
        "properties": {"prop0": "<a click='asdf\"aaa\"asdfasdfaasdf!@#'>aaaaaaa</a>"}
        },
      { "type": "Feature",
        "geometry": {
          "type": "LineString",
          "coordinates": [
            [102.0, -1], [103.0, 1.0], [104.0, 0.0], [105.0, 1.0]
            ]
          },
        "properties": {
          "prop0": "value0",
          "prop1": 0.0
          }
        },
      { "type": "Feature",
         "geometry": {
           "type": "Polygon",
           "coordinates": [
             [ [100.0, 0.0], [101.0, 0.0], [101.0, 1.0],
               [100.0, 1.0], [100.0, 0.0] ]
             ]
         },
         "properties": {
           "prop0": "value0",
           "prop1": {"this": "that"}
           }
         }
       ]
     }
