## Tips for reverse-engineering TR5

### Bit-fields

Some structures used in Tomb Raider 5 (whose definitions are available in the TYPES.H and SPECTYPES.H headers for most of them) contain bit-fields, i.e. various different fields that each occupy 1 or 2 bits. Example from `COLL_INFO` struct (only the bit-field is shown):

```c
struct COLL_INFO
{
	unsigned short slopes_are_walls : 2; // offset=132.0
	unsigned short slopes_are_pits : 1; // offset=132.2
	unsigned short lava_is_pit : 1; // offset=132.3
	unsigned short enable_baddie_push : 1; // offset=132.4
	unsigned short enable_spaz : 1; // offset=132.5
	unsigned short hit_ceiling : 1; // offset=132.6
};
```

Here, all of the fields above fit in a single `short` (16-bit signed integer), and the number after the colon represents the number of bits that the field occupies. On a little-endian architecture, the fields above will be stored in the order of their definition (although it is not mandatory by the C standard; the compiler is free to choose any arrangement, but that is the most common case you will stumble open).

The problem is that in IDA Pro, and most other decompilers, bit-fields are not handled correctly, but instead treated as a whole:

- in IDA Pseudocode, they will be shown as `bf_XX` (XX is the offset of the field in hex) and handled as a standalone field)
- in MIPS assembly, the field will be treated the same way as the pseudocode, but will be "referenced" with the offset of the bit-field.

Therefore, operations on bit-fields are mostly bitwise ANDs and ORs (for clearing and setting a field, respectively). Determining which "part" of the bit-field is being cleared or set takes time, it implies converting the instruction value to its binary representation and finding which bits corresponds to which field. Thus, here is a cheatsheet of common bit-fields operations.

<table>
 <tr><th>Structure</th><th>Operation</th><th>Value</th><th>Result</th></tr>
 <tr><td rowspan=3><pre>ITEM_INFO</pre></td><td rowspan=2>And assign</td><td><pre>0xFFF9</pre></td><td><pre>item.status = 0;</pre></td></tr>
 <tr><td><pre>0xFFF7</pre></td><td><pre>item.gravity_status = 0;</pre></td></tr>
 <tr><td>Or assign</td><td>2</td><td><pre>item.status = 1;</pre></td></tr>
 <tr><td rowspan=4><pre>lara_info</pre></td><td rowspan=2>And check</td><td><pre>0x40</pre></td><td><pre>lara.CanMonkeySwing</pre></td></tr>
 <tr><td><pre>0x20</pre></td><td><pre>lara.IsMoving</pre></td></tr>
 <tr><td rowspan=2>And assign</td><td><pre>0xFFFB</pre></td><td><pre>lara.look = 0;</pre></td></tr>
 <tr><td><pre>0xDFFF</pre></td><td><pre>lara.Busy = 0;</pre></td>
 <tr><td rowspan=4><pre>COLL_INFO</pre></td><td rowspan=3>And assign</td><td><pre>0xFFCF</pre></td><td><pre>coll.enable_spaz = 0;
coll.enable_baddie_push = 0;</pre></td></tr>
 <tr><td><pre>0xFFDF</pre></td><td><pre>coll.enable_spaz = 0;</pre></td></tr>
 <tr><td><pre>0xFFEF</pre></td><td><pre>coll.enable_baddie_push = 0;</pre></td></tr>
 <tr><td>Or assign</td><td><pre>0x10</pre></td><td><pre>coll.enable_baddie_push = 1;</pre></td></tr>
</table>