# Kanto-Verse tilesets

Tiles by **Alchemybats** (credit required by the original sheet), split into GBA-sized tilesets.

| Folder | Type | Size | Palettes |
|---|---|---|---|
| `kanto_general/` | primary | 637 / 640 tiles, 472 metatiles | 00–06 |
| `vermilion_dock/` | secondary | 383 / 384 tiles, 280 metatiles | 07–11 |

Each folder has `tiles.png` (4bpp indexed, unique 8×8 tiles), `palettes/00.pal`–`15.pal` (JASC),
`metatiles.bin`, `metatile_attributes.bin` and `preview.png` (the metatiles as Porymap shows them).
The live copies used by the game are `data/tilesets/primary/kv_general` and
`data/tilesets/secondary/kv_vermilion_dock`.

- **kanto_general**: grass (3 families), flowers, tall grass, bushes, water, ledges (grass, medium,
  dark, water), dirt paths, ponds/shorelines on bright and dark grass, sand patch, grass plateaus
  (bright, medium, dark), plain floors (concrete, asphalt, tan dirt, cobbled dirt, dirt, lime, dark dirt,
  dark cobble), two green trees, wooden sign, Pokémon Center, Mart.
- **vermilion_dock**: pier planks on water, yacht, second ship (`ship2.png`), stone platforms on water (`platforms.png`, gold fences removed, asphalt on top), plank bridge over a platform edge (`plank_bridge.png`), lighthouse, blue house.

## Using the tilesets

To build the game with them, see [Building the game](../README.md#building-the-game).

Maps that use these tilesets need `"layout_version": "frlg"` on their layout in
`data/layouts/layouts.json`. Without it, the game reads the block behaviors (tall grass, water,
ledges, doors) in the wrong format.
