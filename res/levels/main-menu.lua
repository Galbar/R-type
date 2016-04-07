return {
  version = "1.1",
  luaversion = "5.1",
  tiledversion = "0.12.3",
  orientation = "orthogonal",
  width = 13,
  height = 9,
  tilewidth = 80,
  tileheight = 80,
  nextobjectid = 4,
  properties = {},
  tilesets = {
    {
      name = "main-menu-background-animation",
      firstgid = 1,
      tilewidth = 80,
      tileheight = 80,
      spacing = 0,
      margin = 0,
      image = "../textures/main-menu-background-animation.png",
      imagewidth = 800,
      imageheight = 320,
      tileoffset = {
        x = 0,
        y = 0
      },
      properties = {},
      terrains = {},
      tiles = {
        {
          id = 0,
          animation = {
            {
              tileid = "0",
              duration = "100"
            },
            {
              tileid = "20",
              duration = "100"
            }
          }
        },
        {
          id = 1,
          animation = {
            {
              tileid = "1",
              duration = "100"
            },
            {
              tileid = "21",
              duration = "100"
            }
          }
        },
        {
          id = 2,
          animation = {
            {
              tileid = "2",
              duration = "100"
            },
            {
              tileid = "22",
              duration = "100"
            }
          }
        },
        {
          id = 3,
          animation = {
            {
              tileid = "3",
              duration = "100"
            },
            {
              tileid = "23",
              duration = "100"
            }
          }
        },
        {
          id = 4,
          animation = {
            {
              tileid = "4",
              duration = "100"
            },
            {
              tileid = "24",
              duration = "100"
            }
          }
        },
        {
          id = 5,
          animation = {
            {
              tileid = "5",
              duration = "100"
            },
            {
              tileid = "25",
              duration = "100"
            }
          }
        },
        {
          id = 6,
          animation = {
            {
              tileid = "6",
              duration = "100"
            },
            {
              tileid = "26",
              duration = "100"
            }
          }
        },
        {
          id = 7,
          animation = {
            {
              tileid = "7",
              duration = "100"
            },
            {
              tileid = "27",
              duration = "100"
            }
          }
        },
        {
          id = 8,
          animation = {
            {
              tileid = "8",
              duration = "100"
            },
            {
              tileid = "28",
              duration = "100"
            }
          }
        },
        {
          id = 9,
          animation = {
            {
              tileid = "9",
              duration = "100"
            },
            {
              tileid = "29",
              duration = "100"
            }
          }
        },
        {
          id = 10,
          animation = {
            {
              tileid = "10",
              duration = "100"
            },
            {
              tileid = "30",
              duration = "100"
            }
          }
        },
        {
          id = 11,
          animation = {
            {
              tileid = "11",
              duration = "100"
            },
            {
              tileid = "31",
              duration = "100"
            }
          }
        },
        {
          id = 16,
          animation = {
            {
              tileid = "16",
              duration = "100"
            },
            {
              tileid = "36",
              duration = "100"
            }
          }
        },
        {
          id = 17,
          animation = {
            {
              tileid = "17",
              duration = "100"
            },
            {
              tileid = "37",
              duration = "100"
            }
          }
        },
        {
          id = 18,
          animation = {
            {
              tileid = "18",
              duration = "100"
            },
            {
              tileid = "38",
              duration = "100"
            }
          }
        }
      }
    },
    {
      name = "main-menu-background",
      firstgid = 41,
      tilewidth = 80,
      tileheight = 80,
      spacing = 0,
      margin = 0,
      image = "../textures/main-menu-background.jpg",
      imagewidth = 1024,
      imageheight = 720,
      tileoffset = {
        x = 0,
        y = 0
      },
      properties = {},
      terrains = {},
      tiles = {
        {
          id = 72,
          animation = {
            {
              tileid = "72",
              duration = "100"
            },
            {
              tileid = "73",
              duration = "100"
            },
            {
              tileid = "74",
              duration = "100"
            },
            {
              tileid = "75",
              duration = "100"
            },
            {
              tileid = "76",
              duration = "100"
            }
          }
        }
      }
    }
  },
  layers = {
    {
      type = "imagelayer",
      name = "Image Layer 1",
      x = 0,
      y = 0,
      visible = true,
      opacity = 1,
      image = "../textures/main-menu-background.jpg",
      properties = {}
    },
    {
      type = "tilelayer",
      name = "Tile Layer 1",
      x = 0,
      y = 0,
      width = 13,
      height = 9,
      visible = true,
      opacity = 1,
      properties = {},
      encoding = "lua",
      data = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3,
        11, 12, 0, 0, 0, 0, 17, 18, 19, 0, 11, 12, 13,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    },
    {
      type = "imagelayer",
      name = "Image Layer 2",
      x = 298,
      y = 281,
      visible = true,
      opacity = 1,
      image = "../textures/main-menu-play-btn.png",
      properties = {}
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
          type = "ChangeLevelButton",
          shape = "rectangle",
          x = 298,
          y = 279,
          width = 432,
          height = 190,
          rotation = 0,
          visible = true,
          properties = {
            ["target"] = "level1"
          }
        }
      }
    }
  }
}
