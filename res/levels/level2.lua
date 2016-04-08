return {
  version = "1.1",
  luaversion = "5.1",
  tiledversion = "0.12.3",
  orientation = "orthogonal",
  width = 30,
  height = 9,
  tilewidth = 80,
  tileheight = 80,
  nextobjectid = 28,
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
          id = 697,
          animation = {
            {
              tileid = "697",
              duration = "500"
            },
            {
              tileid = "726",
              duration = "500"
            }
          }
        }
      }
    }
  },
  layers = {
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
        437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446,
        466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475,
        495, 496, 497, 498, 499, 500, 501, 502, 503, 504, 495, 496, 497, 498, 499, 500, 501, 502, 503, 504, 495, 496, 497, 498, 499, 500, 501, 502, 503, 504,
        524, 525, 526, 527, 528, 529, 530, 531, 532, 533, 524, 525, 526, 527, 528, 529, 530, 531, 532, 533, 524, 525, 526, 527, 528, 529, 530, 531, 532, 533,
        553, 554, 555, 556, 557, 558, 559, 560, 561, 562, 553, 554, 555, 556, 557, 558, 559, 560, 561, 562, 553, 554, 555, 556, 557, 558, 559, 560, 561, 562,
        582, 583, 584, 585, 586, 587, 588, 589, 590, 591, 582, 583, 584, 585, 586, 587, 588, 589, 590, 591, 582, 583, 584, 585, 586, 587, 588, 589, 590, 591,
        611, 612, 613, 614, 615, 616, 617, 618, 619, 620, 611, 612, 613, 614, 615, 616, 617, 618, 619, 620, 611, 612, 613, 614, 615, 616, 617, 618, 619, 620,
        640, 641, 642, 643, 644, 645, 646, 647, 648, 649, 640, 641, 642, 643, 644, 645, 646, 647, 648, 649, 640, 641, 642, 643, 644, 645, 646, 647, 648, 649,
        669, 670, 671, 672, 673, 674, 675, 676, 677, 678, 669, 670, 671, 672, 673, 674, 675, 676, 677, 678, 669, 670, 671, 672, 673, 674, 675, 676, 677, 678
      }
    },
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
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698, 698,
        621, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 623
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
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 534, 535, 0, 0, 534, 535, 534, 535, 0, 0, 534, 535, 0, 0, 534, 535, 0, 0, 0, 0, 0, 0, 0, 0, 534, 535, 0, 0,
        0, 0, 563, 564, 0, 0, 563, 564, 563, 564, 565, 0, 563, 564, 0, 0, 563, 564, 0, 0, 0, 565, 0, 0, 0, 565, 563, 564, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    },
    {
      type = "objectgroup",
      name = "Object Layer 1",
      visible = true,
      opacity = 1,
      properties = {},
      objects = {
        {
          id = 1,
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
          id = 3,
          name = "",
          type = "Rabbit",
          shape = "rectangle",
          x = 1556.54,
          y = 605.939,
          width = 32,
          height = 32,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 5,
          name = "",
          type = "Rabbit",
          shape = "rectangle",
          x = 1129.7,
          y = 605.394,
          width = 32,
          height = 32,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 6,
          name = "",
          type = "Rabbit",
          shape = "rectangle",
          x = 608.485,
          y = 599.394,
          width = 32,
          height = 32,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 7,
          name = "",
          type = "Bird",
          shape = "rectangle",
          x = 2139.39,
          y = 212.121,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 8,
          name = "",
          type = "Bird",
          shape = "rectangle",
          x = 1636.36,
          y = 200,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 9,
          name = "",
          type = "Bird",
          shape = "rectangle",
          x = 1512.12,
          y = 406.061,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 10,
          name = "",
          type = "Bird",
          shape = "rectangle",
          x = 1351.52,
          y = 193.939,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 11,
          name = "",
          type = "Bird",
          shape = "rectangle",
          x = 1284.85,
          y = 333.333,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 12,
          name = "",
          type = "Bird",
          shape = "rectangle",
          x = 1009.09,
          y = 139.394,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 13,
          name = "",
          type = "Bird",
          shape = "rectangle",
          x = 733.333,
          y = 212.121,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 14,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 1093.94,
          y = 427.273,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {
            ["shooter"] = "true"
          }
        },
        {
          id = 15,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 1872.73,
          y = 396.97,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {
            ["shooter"] = "true"
          }
        },
        {
          id = 16,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 1978.79,
          y = 142.424,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 17,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 421.212,
          y = 569.697,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 18,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 1406.06,
          y = 612.121,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 19,
          name = "",
          type = "Owl",
          shape = "rectangle",
          x = 1309.09,
          y = 460.606,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 20,
          name = "",
          type = "Player",
          shape = "rectangle",
          x = 34.6667,
          y = 270.091,
          width = 64,
          height = 78,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 21,
          name = "",
          type = "BigButterfly",
          shape = "rectangle",
          x = 2248.48,
          y = 409.091,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {}
        },
        {
          id = 22,
          name = "",
          type = "PowerUp",
          shape = "rectangle",
          x = 229.239,
          y = 465.665,
          width = 14.25,
          height = 14.125,
          rotation = 0,
          visible = true,
          properties = {
            ["type"] = "gun"
          }
        },
        {
          id = 23,
          name = "",
          type = "PowerUp",
          shape = "rectangle",
          x = 883.784,
          y = 602.028,
          width = 14.25,
          height = 14.125,
          rotation = 0,
          visible = true,
          properties = {
            ["type"] = "gun"
          }
        },
        {
          id = 24,
          name = "",
          type = "PowerUp",
          shape = "rectangle",
          x = 1338.33,
          y = 468.695,
          width = 14.25,
          height = 14.125,
          rotation = 0,
          visible = true,
          properties = {
            ["type"] = "gun"
          }
        },
        {
          id = 25,
          name = "",
          type = "PowerUp",
          shape = "rectangle",
          x = 1665.6,
          y = 605.059,
          width = 14.25,
          height = 14.125,
          rotation = 0,
          visible = true,
          properties = {
            ["type"] = "gun"
          }
        },
        {
          id = 26,
          name = "",
          type = "PowerUp",
          shape = "rectangle",
          x = 706.061,
          y = 475.758,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {
            ["type"] = "shield"
          }
        },
        {
          id = 27,
          name = "",
          type = "PowerUp",
          shape = "rectangle",
          x = 1051.52,
          y = 615.152,
          width = 0,
          height = 0,
          rotation = 0,
          visible = true,
          properties = {
            ["type"] = "shield"
          }
        }
      }
    }
  }
}
