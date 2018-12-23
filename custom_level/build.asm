.include "macros.asm"

.n64
.open "ys.z64", "ys-smb.z64", 0

.headersize 0x01000000

.org 0x01EBDA70

tile_data: .incbin "tile_data.bin"
.definelabel tile_data_size, (org()-tile_data)

palette: .incbin "palette.bin"
.definelabel palette_size, (org()-palette)

tile_map: .incbin "tile_map.bin"
.definelabel tile_map_size, (org()-tile_map)

collision: .incbin "collision.bin"
.definelabel collision_size, (org()-collision)

object_placements:
.include "object_placements.asm"
.definelabel object_placements_size, (org()-object_placements)
.definelabel num_object_placements, (object_placements_size / 12)

.org 0x0154ACB0
.dw tile_data_size, tile_data_size, tile_data

.org 0x0154ACF8
.dw palette_size, palette_size, palette

.org 0x0154AD94
.dw tile_map_size, tile_map_size, tile_map

.org 0x0154ADDC
.dw collision_size, collision_size, collision

.org 0x01B52110
.dh num_object_placements, 0x0000
.dw object_placements

.close
