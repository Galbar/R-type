return {
  version = "1.1",
  luaversion = "5.1",
  tiledversion = "0.12.3",
  orientation = "orthogonal",
  width = 30,
  height = 9,
  tilewidth = 80,
  tileheight = 80,
  nextobjectid = 25,
  properties = {
    ["camera_speed"] = "1"
  },
  tilesets = {
    {
      name = "Seasonal platformer tiles",
      firstgid = 1,
      tilewidth = 80,
      tileheight = 80,
      spacing = 0,
      margin = 0,
      image = "../textures/Seasonal platformer tiles.png",
      imagewidth = 2320,
      imageheight = 2160,
      tileoffset = {
        x = 0,
        y = 0
      },
      properties = {},
      terrains = {},
      tiles = {
        {
          id = 291,
          animation = {
            {
              tileid = "291",
              duration = "100"
            },
            {
              tileid = "349",
              duration = "100"
            }
          }
        },
        {
          id = 292,
          animation = {
            {
              tileid = "292",
              duration = "100"
            },
            {
              tileid = "350",
              duration = "100"
            }
          }
        },
        {
          id = 293,
          animation = {
            {
              tileid = "293",
              duration = "100"
            },
            {
              tileid = "351",
              duration = "100"
            }
          }
        },
        {
          id = 294,
          animation = {
            {
              tileid = "294",
              duration = "100"
            },
            {
              tileid = "352",
              duration = "100"
            }
          }
        },
        {
          id = 295,
          animation = {
            {
              tileid = "295",
              duration = "100"
            },
            {
              tileid = "353",
              duration = "100"
            }
          }
        },
        {
          id = 296,
          animation = {
            {
              tileid = "296",
              duration = "100"
            },
            {
              tileid = "354",
              duration = "100"
            }
          }
        },
        {
          id = 297,
          animation = {
            {
              tileid = "297",
              duration = "100"
            },
            {
              tileid = "355",
              duration = "100"
            }
          }
        },
        {
          id = 298,
          animation = {
            {
              tileid = "298",
              duration = "100"
            },
            {
              tileid = "356",
              duration = "100"
            }
          }
        },
        {
          id = 299,
          animation = {
            {
              tileid = "299",
              duration = "100"
            },
            {
              tileid = "357",
              duration = "100"
            }
          }
        },
        {
          id = 300,
          animation = {
            {
              tileid = "300",
              duration = "100"
            },
            {
              tileid = "358",
              duration = "100"
            }
          }
        },
        {
          id = 321,
          animation = {
            {
              tileid = "321",
              duration = "100"
            },
            {
              tileid = "379",
              duration = "100"
            }
          }
        },
        {
          id = 327,
          animation = {
            {
              tileid = "327",
              duration = "100"
            },
            {
              tileid = "385",
              duration = "100"
            }
          }
        },
        {
          id = 328,
          animation = {
            {
              tileid = "328",
              duration = "100"
            },
            {
              tileid = "386",
              duration = "100"
            }
          }
        }
      }
    }
  },
  layers = {
    {
      type = "tilelayer",
      name = "Tile Layer 1",
      x = 0,
      y = 0,
      width = 30,
      height = 9,
      visible = true,
      opacity = 1,
      properties = {},
      encoding = "lua",
      data = {
        31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
        89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98,
        118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
        147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156,
        176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185,
        205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214,
        234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243,
        263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272
      }
    },
    {
      type = "tilelayer",
      name = "Tile Layer 2",
      x = 0,
      y = 0,
      width = 30,
      height = 9,
      visible = true,
      opacity = 1,
      properties = {},
      encoding = "lua",
      data = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 244, 245, 246, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 244, 245, 246, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 244, 245, 246, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 215, 216, 217, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 244, 245, 246, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        292, 293, 294, 244, 245, 246, 298, 299, 300, 301, 292, 215, 216, 217, 296, 297, 298, 299, 300, 301, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301,
        321, 322, 323, 244, 245, 246, 327, 328, 329, 330, 321, 244, 245, 246, 325, 326, 327, 328, 329, 330, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330,
        216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216
      }
    },
    {
      type = "objectgroup",
      name = "Walls",
      visible = true,
      opacity = 1,
      properties = {},
      objects = {
        {
          id = 1,
          name = "",
          type = "Player",
          shape = "rectangle",
          x = 98,
          y = 264,
          width = 64,
          height = 78,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 2,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 240,
          y = 320,
          width = 240,
          height = 320,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 3,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 0,
          y = 640,
          width = 2400,
          height = 80,
          rotation = 0,
          visible = true,
          properties = {
            ["no_handle"] = "true"
          }
        },
        {
          id = 4,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 880,
          y = 480,
          width = 240,
          height = 160,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 5,
          name = "",
          type = "Wall",
          shape = "rectangle",
          x = 880,
          y = 0,
          width = 240,
          height = 240,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 23,
          name = "",
          type = "Bee",
          shape = "rectangle",
          x = 2245.45,
          y = 124.242,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {
            ["next_level"] = "level2"
          }
        },
        {
          id = 24,
          name = "",
          type = "Bee",
          shape = "rectangle",
          x = 1872.73,
          y = 512.121,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        }
      }
    },
    {
      type = "tilelayer",
      name = "Tile Layer 3",
      x = 0,
      y = 0,
      width = 30,
      height = 9,
      visible = true,
      opacity = 1,
      properties = {},
      encoding = "lua",
      data = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 186, 187, 188, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 186, 187, 188, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 128, 129, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 129, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 157, 158, 0, 159, 0, 0, 0, 0, 0, 159, 0, 0, 157, 158, 0, 0, 0, 0, 0, 159, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    },
    {
      type = "objectgroup",
      name = "enemies",
      visible = true,
      opacity = 1,
      properties = {},
      objects = {
        {
          id = 8,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 1315.15,
          y = 436.364,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 10,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 1763.64,
          y = 251.515,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 11,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 1700,
          y = 372.727,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 13,
          name = "",
          type = "Bee",
          shape = "rectangle",
          x = 1406.06,
          y = 103.03,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 14,
          name = "",
          type = "Bee",
          shape = "rectangle",
          x = 845.455,
          y = 324.242,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 16,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 804,
          y = 206,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {
            ["shooter"] = "true"
          }
        },
        {
          id = 17,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 772,
          y = 324,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {
            ["shooter"] = "true"
          }
        },
        {
          id = 18,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 574,
          y = 128,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {
            ["shooter"] = "true"
          }
        },
        {
          id = 19,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 1516,
          y = 210,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {
            ["shooter"] = "true"
          }
        },
        {
          id = 20,
          name = "",
          type = "PowerUp",
          shape = "rectangle",
          x = 364,
          y = 266,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {
            ["type"] = "gun"
          }
        },
        {
          id = 21,
          name = "",
          type = "PowerUp",
          shape = "rectangle",
          x = 1004,
          y = 426,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {
            ["type"] = "shield"
          }
        },
        {
          id = 22,
          name = "",
          type = "PowerUp",
          shape = "rectangle",
          x = 1482,
          y = 609,
          width = 14.25,
          height = 14.125,
          rotation = 0,
          visible = true,
          properties = {
            ["type"] = "gun"
          }
        }
      }
    }
  }
}
