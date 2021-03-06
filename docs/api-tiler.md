# Multi-Stream Tiler API
Tiler components perform frame-rendering from multiple-sources into a 2D grid array with one tile per source.  As with all components, Tilers must be uniquely named from all other components created. Tiler components have dimensions, `width` and `height`, and a number-of-tiles expressed in `rows` and `cols`. A Tiler's dimension must be set on creation, whereas `rows` and `cols` default to 0 indicating best-fit based on the number of sources. Both dimensions and tiles can be updated after Tiler creation, even when the Tiler is currently `in-use` by a Pipeline. A Tiler can be called on to show a single source for an extendable time and return to show all sources on timeout.

#### Tiler Construction and Destruction
Tilers are constructed by calling the constructor [dsl_tiler_new](#dsl_tiler_new). Tilers are deleted by calling [dsl_component_delete](api-component.md#dsl_component_delete), [dsl_component_delete_many](api-component.md#dsl_component_delete_many), or [dsl_component_delete_all](api-component.md#dsl_component_delete_all)

#### Adding to a Pipeline
The relationship between Pipelines/Branches and Tilers is one-to-one. Once added to a Pipeline or Branch, a Tiler must be removed before it can used with another. 

Multi-Stream Tilers are added to a Pipeline by calling [dsl_pipeline_component_add](api-pipeline.md#dsl_pipeline_component_add) or [dsl_pipeline_component_add_many](api-pipeline.md#dsl_pipeline_component_add_many) (when adding with other components) and removed with [dsl_pipeline_component_remove](api-pipeline.md#dsl_pipeline_component_remove), [dsl_pipeline_component_remove_many](api-pipeline.md#dsl_pipeline_component_remove_many), or [dsl_pipeline_component_remove_all](api-pipeline.md#dsl_pipeline_component_remove_all).

#### Adding to a Branch
Tilers are added to Branches by calling [dsl_branch_component_add](api-branch.md#dsl_branch_component_add) or [dsl_branch_component_add_many](api-branch.md#dsl_branch_component_add_many) (when adding with other components) and removed with [dsl_branch_component_remove](api-branch.md#dsl_branch_component_remove), [dsl_branch_component_remove_many](api-branch.md#dsl_branch_component_remove_many), or [dsl_branch_component_remove_all](api-branch.md#dsl_branch_component_remove_all).

#### Adding/Removing Pad-Probe-handlers
Multiple Sink and/or Source [Pad-Probe Handlers](/docs/api-pph/md) can be added to a Tiler by calling [dsl_tiler_pph_add](#dsl_tiler_pph_add) and removed with [dsl_tiler_pph_remove](#dsl_tiler_pph_remove).

## Tiler API
**Constructors**
* [dsl_tiler_new](#dsl_tiler_new)

**Methods**
* [dsl_tiler_dimensions_get](#dsl_tiler_dimensions_get)
* [dsl_tiler_dimensions_set](#dsl_tiler_dimensions_set)
* [dsl_tiler_tiles_get](#dsl_tiler_tiles_get)
* [dsl_tiler_tiles_set](#dsl_tiler_tiles_set)
* [dsl_tiler_source_show_get](#dsl_tiler_source_show_get)
* [dsl_tiler_source_show_set](#dsl_tiler_source_show_set)
* [dsl_tiler_source_show_all](#dsl_tiler_source_show_all)
* [dsl_tiler_pph_add](#dsl_tiler_pph_add).
* [dsl_tiler_pph_remove](#dsl_tiler_pph_remove).

## Return Values
The following return codes are used by the Tiler API
```C++
#define DSL_RESULT_TILER_RESULT                                     0x00070000
#define DSL_RESULT_TILER_NAME_NOT_UNIQUE                            0x00070001
#define DSL_RESULT_TILER_NAME_NOT_FOUND                             0x00070002
#define DSL_RESULT_TILER_NAME_BAD_FORMAT                            0x00070003
#define DSL_RESULT_TILER_THREW_EXCEPTION                            0x00070004
#define DSL_RESULT_TILER_IS_IN_USE                                  0x00070005
#define DSL_RESULT_TILER_SET_FAILED                                 0x00070006
#define DSL_RESULT_TILER_HANDLER_ADD_FAILED                         0x00070007
#define DSL_RESULT_TILER_HANDLER_REMOVE_FAILED                      0x00070008
#define DSL_RESULT_TILER_PAD_TYPE_INVALID                           0x00070009
#define DSL_RESULT_TILER_COMPONENT_IS_NOT_TILER                     0x0007000A
```

## Constructors
### *dsl_tiler_new*
```C++
DslReturnType dsl_tiler_new(const wchar_t* name, uint width, uint height);
```
The constructor creates a uniquely named Tiler with given dimensions. Construction will fail if the name is currently in use. The Tiler is created using the default `rows` and `cols` settings of 0 allowing the Tiler to select a best-fit for the number of [Sources] upstream in the Pipeline. The default values can be updated be calling [dsl_tiler_tiles_set](#dsl_display_tiles_set).

**Parameters**
* `name` - [in] unique name for the Tiler to create.
* `width` - [in] width of the Tilded Display in pixels
* `height` - [in] height of the Tilded Display in pixels

**Returns**
* `DSL_RESULT_SUCCESS` on successful creation. One of the [Return Values](#return-values) defined above on failure

**Python Example**
```Python
retval = dsl_tiler_new('my-tiler', 1280, 720)
```

<br>

## Methods
### *dsl_tiler_dimensions_get*
```C++
DslReturnType dsl_tiler_dimensions_get(const wchar_t* name, uint* width, uint* height);
```
This service returns the current width and height of the named Tiler.

**Parameters**
* `name` - [in] unique name for the Tiler to query.
* `width` - [out] width of the Tiler in pixels.
* `height` - [out] height of the Tiler in pixels.

**Returns**
* `DSL_RESULT_SUCCESS` on successful query. One of the [Return Values](#return-values) defined above on failure

**Python Example**
```Python
retval, width, height = dsl_tiler_dimensions_get('my-tiler')
```

<br>

### *dsl_tiler_dimensions_set*
```C++
DslReturnType dsl_tiler_dimensions_set(const wchar_t* name, uint width, uint height);
```
This service sets the width and height of the named Tiler. This service can be called at any time.

**Parameters**
* `name` - [in] unique name for the Tiler to update.
* `width` - [in] current width of the Tiler in pixels.
* `height` - [in] current height of the Tiler in pixels.

**Returns**
* `DSL_RESULT_SUCCESS` on successful update. One of the [Return Values](#return-values) defined above on failure

**Python Example**
```Python
retval = dsl_tiler_dimensions_get('my-tiler', 1280, 720)
```

<br>

### *dsl_tiler_tiles_get*
```C++
DslReturnType dsl_tiler_tiles_get(const wchar_t* name, uint* cols, uint* rows);
```
This service returns the current columns and rows in use by the named Tiler. Values of 0 - the default – indicate that the is using a best-fit based on the number of Sources upstream in the Pipeline.

**Parameters**
* `name` - [in] unique name for the Tiler to query.
* `cols` - [out] current columns setting for the Tiler.
* `rows` - [out] current rows setting for the Tiler.

**Returns**
* `DSL_RESULT_SUCCESS` on successful query. One of the [Return Values](#return-values) defined above on failure.

**Python Example**
```Python
retval, cols, rows = dsl_tiler_tiles_get('my-tiler')
```

<br>

### *dsl_tiler_tiles_set*
```C++
DslReturnType dsl_tiler_tiles_set(const wchar_t* name, uint cols, uint rows);
```
This service sets the number of columns and rows for the named Tiler. Setting both values to 0 - the default - allows the Tiler to determine a best-fit based on the number of Sources upstream. The number of rows must be at least one half that of columns or the call will fail (e.g. 4x1). The call will also fail if the Tiler is currently `in-use`.

**Parameters**
* `name` - [in] unique name for the Tiler to update.
* `cols` - [in] new columns setting for the Tiler.
* `rows` - [in] new rows setting for the Tiler.

**Returns**
* `DSL_RESULT_SUCCESS` on successful update. One of the [Return Values](#return-values) defined above on failure.

**Python Example**
```Python
retval = dsl_tiler_tiles_set('my-tiler', 3, 2)
```

<br>

### *dsl_tiler_source_show_get*
```C++
DslReturnType dsl_tiler_source_show_get(const wchar_t* name, 
    const wchar_t** source, uint* timeout);
```
This service get the current show-source parameters for the named Tiler. The service returns DSL_TILER_ALL_SOURCES (equal to NULL) to indicate that all sources are shown

**Parameters**
* `name` - [in] unique name for the Tiler to update.
* `source` - [out] unique name of the current source show. `DSL_TILER_ALL_SOURCES` (equal to NULL) indicates that all source (default).
* `timeout` - [out] the remaining number of seconds that the current source will be shown for. A value of 0 indicates show indefinately (default).

**Returns**
* `DSL_RESULT_SUCCESS` on successful update. One of the [Return Values](#return-values) defined above on failure. 

**Python Example**
```Python
retval, current_source, timeout = dsl_tiler_source_show_get('my-tiler')
```

<br>

### *dsl_tiler_source_show_set*
```C++
DslReturnType dsl_tiler_source_show_set(const wchar_t* name, 
    const wchar_t* source, uint timeout, boolean has_presedence);
```
This service sets the current show-source parameters for the named Tiler to show a single Source. The service will fail if the Source name is not found. The timeout parameter controls how long the single Source will be show. 

Calling `dsl_tiler_show_source_set` with the same source name as currently show will adjust the remaining time to the newly provided timeout value.

Calling `dsl_tiler_show_source_set` with a different source name than currently show will switch to the new source, while applying the new timeout, if:
1. the current source setting is set to `DSL_TILER_ALL_SOURCES`
2. the `has_precedence` parameter is set to `True`

Note: It's advised to set the `has_precedence ` value to `False` when controlling the show-source setting with an ODE Action as excessive switching may occur. Set to `True` when calling from a client key or mouse-button callback for immediate control. 

**Parameters**
* `name` - [in] unique name for the Tiler to update.
* `source` - [in] unique name of the source to show. The service will fail if the Source is not found
* `timeout` - [in] the remaining number of seconds that the current source will be shown for. A value of 0 indicates show indefinitely. 
* `has_precedence` - [in] set to true to give this call precedence over the current setting, false to switch only if another source is not currently shown. 

**Returns**
* `DSL_RESULT_SUCCESS` on successful update. One of the [Return Values](#return-values) defined above on failure.

**Python Example**
```Python
retval = dsl_tiler_source_show_set('my-tiler', 'camera-2', 10, True)
```

<br>

### *dsl_tiler_source_show_all*
```C++
DslReturnType dsl_tiler_source_show_set(const wchar_t* name);
```
This service sets the current show-source setting for the named Tiler to `DSL_TILER_ALL_SOURCES`. The service **always** has precedence over any single source show.

**Parameters**
* `name` - [in] unique name for the Tiler to update.

**Returns**
* `DSL_RESULT_SUCCESS` on successful update. One of the [Return Values](#return-values) defined above on failure.

**Python Example**
```Python
retval = dsl_tiler_source_show_all('my-tiler')
```

<br>

### *dsl_tiler_pph_add*
```C++
DslReturnType dsl_tiler_pph_add(const wchar_t* name, const wchar_t* handler, uint pad);
```
This service adds a [Pad Probe Handler](/docs/api-pph.md) to either the Sink or Source pad of the named Tiler.

**Parameters**
* `name` - [in] unique name of the Tiler to update.
* `handler` - [in] unique name of Pad Probe Handler to add
* `pad` - [in] to which of the two pads to add the handler: `DSL_PAD_SIK` or `DSL_PAD SRC`

**Returns**
* `DSL_RESULT_SUCCESS` on successful add. One of the [Return Values](#return-values) defined above on failure.

**Python Example**
* Example using Nvidia's pyds lib to handle batch-meta data

```Python
retval = dsl_tiler_pph_add('my-tiler', 'my-pph-handler', `DSL_PAD_SINK`)
```

<br>

### *dsl_tiler_pph_remove*
```C++
DslReturnType dsl_tiler_pph_remove(const wchar_t* name, const wchar_t* handler, uint pad);
```
This service removes a [Pad Probe Handler](/docs/api-pph.md) from either the Sink or Source pad of the named Tiler. The service will fail if the named handler is not owned by the Tiler

**Parameters**
* `name` - [in] unique name of the Tiler to update.
* `handler` - [in] unique name of Pad Probe Handler to remove
* `pad` - [in] to which of the two pads to remove the handler from: `DSL_PAD_SIK` or `DSL_PAD SRC`

**Returns**
* `DSL_RESULT_SUCCESS` on successful remove. One of the [Return Values](#return-values) defined above on failure.

**Python Example**
```Python
retval = dsl_tiler_pph_remove('my-tiler', 'my-pph-handler', `DSL_PAD_SINK`)
```

<br>

---

## API Reference
* [List of all Services](/docs/api-reference-list.md)
* [Pipeline](/docs/api-pipeline.md)
* [Source](/docs/api-source.md)
* [Tap](/docs/api-tap.md)
* [Dewarper](/docs/api-dewarper.md)
* [Primary and Secondary GIE](/docs/api-gie.md)
* [Tracker](/docs/api-tracker.md)
* **Tiler**
* [On-Screen Display](/docs/api-osd.md)
* [Demuxer and Splitter](/docs/api-tee.md)
* [Sink](/docs/api-sink.md)
* [Pad Probe Handler](/docs/api-pph.md)
* [ODE Trigger](/docs/api-ode-trigger.md)
* [ODE Acton](/docs/api-ode-action.md)
* [ODE Area](/docs/api-ode-area.md)
* [Display Type](/docs/api-display-types.md)
* [Branch](/docs/api-branch.md)
* [Component](/docs/api-component.md)
