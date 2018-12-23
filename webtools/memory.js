const U8  = 'u8';
const U16 = 'u16';
const U32 = 'u32';
const S8  = 's8';
const S16 = 's16';
const S32 = 's32';
const F32 = 'f32';
const F64 = 'f64';

const TYPE_SIZES = {
    'u8':  1,
    'u16': 2,
    'u32': 4,
    's8':  1,
    's16': 2,
    's32': 4,
    'f32': 4,
    'f64': 8
};

function Memory(ab)
{
    this.ab = ab;
    this.dv = new DataView(ab);
    var _this = this;

    this.u8 = new Proxy({}, {
        get: function(obj, prop){return _this.dv.getUint8(prop);},
        set: function(obj, prop, val){_this.dv.setUint8(prop, val);}
    });

    this.u16 = new Proxy({}, {
        get: function(obj, prop){return _this.dv.getUint16(prop);},
        set: function(obj, prop, val){_this.dv.setUint16(prop, val);}
    });

    this.u32 = new Proxy({}, {
        get: function(obj, prop){return _this.dv.getUint32(prop);},
        set: function(obj, prop, val){_this.dv.setUint32(prop, val);}
    });

    this.s8 = new Proxy({}, {
        get: function(obj, prop){return _this.dv.getInt8(prop);},
        set: function(obj, prop, val){_this.dv.setInt8(prop, val);}
    });

    this.s16 = new Proxy({}, {
        get: function(obj, prop){return _this.dv.getInt16(prop);},
        set: function(obj, prop, val){_this.dv.setInt16(prop, val);}
    });

    this.s32 = new Proxy({}, {
        get: function(obj, prop){return _this.dv.getInt32(prop);},
        set: function(obj, prop, val){_this.dv.setInt32(prop, val);}
    });

    this.f32 = new Proxy({}, {
        get: function(obj, prop){return _this.dv.getFloat32(prop);},
        set: function(obj, prop, val){_this.dv.setFloat32(prop, val);}
    });

    this.f64 = new Proxy({}, {
        get: function(obj, prop){return _this.dv.getFloat64(prop);},
        set: function(obj, prop, val){_this.dv.setFloat64(prop, val);}
    });
}

Memory._structPrettyPrint = function()
{
    var str = "";

    str += "@ " + this.__base.hex() + ":\n";

    for(fieldName in this.__structure)
    {
        var value = this.__proxy[fieldName];
        var fieldInfo = this.__structure[fieldName];
        var typeSize = fieldInfo.typeSize;
        var typeName = fieldInfo.typeName;
        var offset = fieldInfo.structOffset;
        str += "/*0x" + offset.hex(2) + "*/ " + typeName + " " + fieldName + ": 0x" + value.hex(typeSize * 2) + "\n";
    }

    return str;
}

Memory.prototype.struct = function(base, layout)
{
    var structure = {};
    var base = base;
    var mem = this;

    var structOffset = 0;

    for(var field in layout)
    {
        var typeName = layout[field];

        if(typeof(typeName) == 'number')
        {
            // padding
            structOffset += typeName;
            continue;
        }

        var typeSize = TYPE_SIZES[typeName];

        structure[field] = {
            structOffset: structOffset,
            typeName: layout[field],
            typeSize: typeSize,
        };

        structOffset += typeSize;
    }

    var meta = {
        __mem: mem,
        __base: base,
        __size: structOffset,
        __structure: structure
    };

    meta.__proxy = new Proxy(meta, {
        get: function(meta, prop)
        {
            if(prop == '__prettyPrint')
            {
                return Memory._structPrettyPrint.bind(meta);
            }

            if(prop in meta)
            {
                return meta[prop];
            }

            if(prop in structure)
            {
                var fieldInfo = structure[prop];
                var typeName = fieldInfo.typeName;
                var structOffset = fieldInfo.structOffset;
                return meta.__mem[typeName][meta.__base + structOffset];
            }
        },
        set: function(meta, prop, value)
        {
            if(prop in meta)
            {
                meta[prop] = value;
                return;
            }

            if(prop in structure)
            {
                var fieldInfo = structure[prop];
                var typeName = fieldInfo.typeName;
                var structOffset = fieldInfo.structOffset;
                meta.__mem[typeName][meta.__base + structOffset] = value;
            }
        }
    });

    return meta.__proxy;
}

Number.prototype.hex = function(len)
{
    var len = len || 8;
    var h = this.toString(16).toUpperCase();
    while(h.length < len)
    {
        h = "0" + h;
    }
    return h;
}