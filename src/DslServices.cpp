/*
The MIT License

Copyright (c) 2019-Present, ROBERT HOWELL

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in-
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "Dsl.h"
#include "DslApi.h"
#include "DslServices.h"

GST_DEBUG_CATEGORY(GST_CAT_DSL);

#define RETURN_IF_PIPELINE_NAME_NOT_FOUND(_pipelines_, _name_) do \
{ \
    if (!_pipelines_[_name_]) \
    { \
        LOG_ERROR("Pipeline name '" << _name_ << "' was not found"); \
        return DSL_RESULT_PIPELINE_NAME_NOT_FOUND; \
    } \
}while(0); 
    
#define RETURN_IF_COMPONENT_NAME_NOT_FOUND(_components_, _name_) do \
{ \
    if (!_components_[_name_]) \
    { \
        LOG_ERROR("Component name '" << _name_ << "' was not found"); \
        return DSL_RESULT_COMPONENT_NAME_NOT_FOUND; \
    } \
}while(0); 

#define INIT_MEMORY(m) memset(&m, 0, sizeof(m));
#define INIT_STRUCT(type, name) struct type name; INIT_MEMORY(name) 
/**
 * Function to handle program interrupt signal.
 * It installs default handler after handling the interrupt.
 */
static void PrgItrSigIsr(int signum)
{
    INIT_STRUCT(sigaction, sa);

    sa.sa_handler = SIG_DFL;

    sigaction(SIGINT, &sa, NULL);

    g_main_loop_quit(DSL::Services::GetServices()->GetMainLoopHandle());
}

/**
 * Function to install custom handler for program interrupt signal.
 */
static void PrgItrSigIsrInstall(void)
{
    INIT_STRUCT(sigaction, sa);

    sa.sa_handler = PrgItrSigIsr;

    sigaction(SIGINT, &sa, NULL);
}    

DslReturnType dsl_source_csi_new(const char* name, 
    uint width, uint height, uint fps_n, uint fps_d)
{
    return DSL::Services::GetServices()->SourceCsiNew(name, 
        width, height, fps_n, fps_d);
}

DslReturnType dsl_source_uri_new(const char* name, 
    const char* uri, uint cudadec_mem_type, uint intra_decode)
{
    return DSL::Services::GetServices()->SourceUriNew(name,
        uri, cudadec_mem_type, intra_decode);
}

boolean dsl_source_is_live(const char* name)
{
    return DSL::Services::GetServices()->SourceIsLive(name);
}

uint dsl_source_get_num_in_use()
{
    return DSL::Services::GetServices()->GetNumSourceInUse();
}

uint dsl_source_get_num_in_use_max()
{
    return DSL::Services::GetServices()->GetNumSourceInUseMax();
}

void dsl_source_set_num_in_use_max(uint max)
{
    return DSL::Services::GetServices()->SetNumSourceInUseMax(max);
}

DslReturnType dsl_sink_overlay_new(const char* name,
    uint offsetX, uint offsetY, uint width, uint height)
{
    return DSL::Services::GetServices()->OverlaySinkNew(name, 
        offsetX, offsetY, width, height);
}

DslReturnType dsl_osd_new(const char* name, boolean isClockEnabled)
{
    return DSL::Services::GetServices()->OsdNew(name, isClockEnabled);
}

DslReturnType dsl_display_new(const char* name, uint width, uint height)
{
    return DSL::Services::GetServices()->DisplayNew(name, width, height);
}

DslReturnType dsl_gie_primary_new(const char* name, const char* inferConfigFile,
    const char* modelEngineFile, uint interval, uint uniqueId)
{
    return DSL::Services::GetServices()->PrimaryGieNew(name, inferConfigFile,
        modelEngineFile, interval, uniqueId);
}

DslReturnType dsl_component_delete(const char* component)
{
    return DSL::Services::GetServices()->ComponentDelete(component);
}

DslReturnType dsl_component_delete_many(const char** names)
{
    return DSL::Services::GetServices()->ComponentDeleteMany(names);
}

DslReturnType dsl_component_delete_all()
{
    return DSL::Services::GetServices()->ComponentDeleteAll();
}

uint dsl_component_list_size()
{
    return DSL::Services::GetServices()->ComponentListSize();
}

const char** dsl_component_list_all()
{
    return DSL::Services::GetServices()->ComponentListAll();
}

DslReturnType dsl_pipeline_new(const char* pipeline)
{
    return DSL::Services::GetServices()->PipelineNew(pipeline);
}

DslReturnType dsl_pipeline_new_many(const char** pipelines)
{
    return DSL::Services::GetServices()->PipelineNewMany(pipelines);
}

DslReturnType dsl_pipeline_delete(const char* pipeline)
{
    return DSL::Services::GetServices()->PipelineDelete(pipeline);
}

DslReturnType dsl_pipeline_delete_many(const char** pipelines)
{
    return DSL::Services::GetServices()->PipelineDeleteMany(pipelines);
}

DslReturnType dsl_pipeline_delete_all()
{
    return DSL::Services::GetServices()->PipelineDeleteAll();
}

uint dsl_pipeline_list_size()
{
    return DSL::Services::GetServices()->PipelineListSize();
}

const char** dsl_pipeline_list_all()
{
    return DSL::Services::GetServices()->PipelineListAll();
}

DslReturnType dsl_pipeline_component_add(const char* pipeline, 
    const char* component)
{
    return DSL::Services::GetServices()->PipelineComponentAdd(pipeline, component);
}

DslReturnType dsl_pipeline_component_add_many(const char* pipeline, 
    const char** components)
{
    return DSL::Services::GetServices()->PipelineComponentAddMany(pipeline, components);
}

DslReturnType dsl_pipeline_component_remove(const char* pipeline, 
    const char* component)
{
    return DSL::Services::GetServices()->PipelineComponentRemove(pipeline, component);
}

DslReturnType dsl_pipeline_component_remove_many(const char* pipeline, 
    const char** components)
{
    return DSL::Services::GetServices()->PipelineComponentRemoveMany(pipeline, components);
}

DslReturnType dsl_pipeline_streammux_set_batch_properties(const char* pipeline, 
    uint batchSize, uint batchTimeout)
{
    return DSL::Services::GetServices()->PipelineStreamMuxSetBatchProperties(pipeline,
        batchSize, batchTimeout);
}

DslReturnType dsl_pipeline_streammux_set_output_size(const char* pipeline, 
    uint width, uint height)
{
    return DSL::Services::GetServices()->PipelineStreamMuxSetOutputSize(pipeline,
        width, height);
}
 
DslReturnType dsl_pipeline_pause(const char* pipeline)
{
    return DSL::Services::GetServices()->PipelinePause(pipeline);
}

DslReturnType dsl_pipeline_play(const char* pipeline)
{
    return DSL::Services::GetServices()->PipelinePlay(pipeline);
}

DslReturnType dsl_pipeline_get_state(const char* pipeline)
{
    return DSL::Services::GetServices()->PipelineGetState(pipeline);
}

DslReturnType dsl_pipeline_dump_to_dot(const char* pipeline, char* filename)
{
    return DSL::Services::GetServices()->PipelineDumpToDot(pipeline, filename);
}

DslReturnType dsl_pipeline_dump_to_dot_with_ts(const char* pipeline, char* filename)
{
    return DSL::Services::GetServices()->PipelineDumpToDotWithTs(pipeline, filename);    
}

DslReturnType dsl_pipeline_state_change_listener_add(const char* pipeline, 
    dsl_state_change_listener_cb listener, void* userdata)
{
    return DSL::Services::GetServices()->
        PipelineStateChangeListenerAdd(pipeline, listener, userdata);
}

DslReturnType dsl_pipeline_state_change_listener_remove(const char* pipeline, 
    dsl_state_change_listener_cb listener)
{
    return DSL::Services::GetServices()->
        PipelineStateChangeListenerRemove(pipeline, listener);
}

DslReturnType dsl_pipeline_display_event_handler_add(const char* pipeline, 
    dsl_display_event_handler_cb handler, void* userdata)
{
    return DSL::Services::GetServices()->
        PipelineDisplayEventHandlerAdd(pipeline, handler, userdata);
}    

DslReturnType dsl_pipeline_display_event_handler_remove(const char* pipeline, 
    dsl_display_event_handler_cb handler)
{
    return DSL::Services::GetServices()->
        PipelineDisplayEventHandlerRemove(pipeline, handler);
}

void dsl_main_loop_run()
{
    PrgItrSigIsrInstall();
    g_main_loop_run(DSL::Services::GetServices()->GetMainLoopHandle());
}


namespace DSL
{
    // Initialize the Services's single instance pointer
    Services* Services::m_pInstatnce = NULL;

    std::string Services::m_configFileDir = DS_CONFIG_DIR;
    std::string Services::m_modelFileDir = DS_MODELS_DIR;
    std::string Services::m_streamFileDir = DS_STREAMS_DIR;
    
    Services* Services::GetServices()
    {
        
        // one time initialization of the single instance pointer
        if (!m_pInstatnce)
        {
            // If gst has not been initialized by the client software
            if (!gst_is_initialized())
            {
                int argc = 0;
                char** argv = NULL;
                
                // initialize the GStreamer library
                gst_init(&argc, &argv);
            }

            // Initialize the single debug category used by the lib
            GST_DEBUG_CATEGORY_INIT(GST_CAT_DSL, "DSL", 0, "DeepStream Services");
            
            // Safe to start logging
            LOG_INFO("Services Initialization");

            m_pInstatnce = new Services();
        }
        return m_pInstatnce;
    }
        
    Services::Services()
        : m_pMainLoop(g_main_loop_new(NULL, FALSE))
        , m_numSourceInUseMax(DSL_DEFAULT_SOURCE_IN_USE_MAX)
    {
        LOG_FUNC();
        
        g_mutex_init(&m_servicesMutex);
    }

    Services::~Services()
    {
        LOG_FUNC();
        
        {
            LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
            
            if (m_pMainLoop)
            {
                LOG_WARN("Main loop is still running!");
                g_main_loop_quit(m_pMainLoop);
            }
        }
        
        g_mutex_clear(&m_servicesMutex);
    }
    
    DslReturnType Services::SourceCsiNew(const char* name,
        uint width, uint height, uint fps_n, uint fps_d)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        // ensure component name uniqueness 
        if (m_components[name])
        {   
            LOG_ERROR("Source name '" << name << "' is not unique");
            return DSL_RESULT_SOURCE_NAME_NOT_UNIQUE;
        }
        try
        {
            m_components[name] = DSL_CSI_SOURCE_NEW(name, width, height, fps_n, fps_d);
        }
        catch(...)
        {
            LOG_ERROR("New CSI Source '" << name << "' threw exception on create");
            return DSL_RESULT_SOURCE_THREW_EXCEPTION;
        }
        LOG_INFO("new CSI Source '" << name << "' created successfully");

        return DSL_RESULT_SUCCESS;
    }
    
    DslReturnType Services::SourceUriNew(const char* name,
        const char* uri, uint cudadecMemType, uint intraDecode)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        // ensure component name uniqueness 
        if (m_components[name])
        {   
            LOG_ERROR("Source name '" << name << "' is not unique");
            return DSL_RESULT_SOURCE_NAME_NOT_UNIQUE;
        }

        std::string streamFilePathSpec = m_streamFileDir;
        streamFilePathSpec.append("/");
        streamFilePathSpec.append(uri);
        
        std::ifstream streamFile(streamFilePathSpec.c_str());
        if (!streamFile.good())
        {
            LOG_ERROR("URI stream file not found");
            return DSL_RESULT_SOURCE_STREAM_FILE_NOT_FOUND;
        }
        streamFilePathSpec.insert(0,"file:");
        LOG_INFO("URI stream file: " << streamFilePathSpec);
        try
        {
            m_components[name] = DSL_URI_SOURCE_NEW(
                name, streamFilePathSpec.c_str(), cudadecMemType, intraDecode);
        }
        catch(...)
        {
            LOG_ERROR("New URI Source '" << name << "' threw exception on create");
            return DSL_RESULT_SOURCE_THREW_EXCEPTION;
        }
        LOG_INFO("new URI Source '" << name << "' created successfully");

        return DSL_RESULT_SUCCESS;
    }

    boolean Services::SourceIsLive(const char* name)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_COMPONENT_NAME_NOT_FOUND(m_components, name);
        
        try
        {
            return std::dynamic_pointer_cast<SourceBintr>(m_components[name])->IsLive();
        }
        catch(...)
        {
            LOG_ERROR("Component '" << name << "' threw exception on create");
            return DSL_RESULT_SOURCE_THREW_EXCEPTION;
        }
    }
    
    uint Services::GetNumSourceInUse()
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        uint numInUse(0);
        
        for (auto const& imap: m_pipelines)
        {
            numInUse += imap.second->GetNumSourceInUse();
        }
        return numInUse;
    }
    
    uint Services::GetNumSourceInUseMax()
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        
        return m_numSourceInUseMax;
    }
    
    void Services::SetNumSourceInUseMax(uint max)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        m_numSourceInUseMax = max;
    }

    DslReturnType Services::OverlaySinkNew(const char* name, 
        uint offsetX, uint offsetY, uint width, uint height)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        // ensure component name uniqueness 
        if (m_components[name])
        {   
            LOG_ERROR("Sink name '" << name << "' is not unique");
            return DSL_RESULT_SINK_NAME_NOT_UNIQUE;
        }
        try
        {
            m_components[name] = DSL_OVERLAY_SINK_NEW(name, offsetX, offsetY, width, height);
        }
        catch(...)
        {
            LOG_ERROR("New Sink '" << name << "' threw exception on create");
            return DSL_RESULT_SINK_NEW_EXCEPTION;
        }
        LOG_INFO("new Sink '" << name << "' created successfully");

        return DSL_RESULT_SUCCESS;
    }
    
    DslReturnType Services::OsdNew(const char* name, boolean isClockEnabled)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        // ensure component name uniqueness 
        if (m_components[name])
        {   
            LOG_ERROR("OSD name '" << name << "' is not unique");
            return DSL_RESULT_OSD_NAME_NOT_UNIQUE;
        }
        try
        {   
            m_components[name] = std::shared_ptr<Bintr>(new OsdBintr(
                name, isClockEnabled));
        }
        catch(...)
        {
            LOG_ERROR("New OSD '" << name << "' threw exception on create");
            return DSL_RESULT_SINK_NEW_EXCEPTION;
        }
        LOG_INFO("new OSD '" << name << "' created successfully");

        return DSL_RESULT_SUCCESS;
    }
    
    DslReturnType Services::DisplayNew(const char* name, 
        uint width, uint height)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        // ensure component name uniqueness 
        if (m_components[name])
        {   
            LOG_ERROR("Display name '" << name << "' is not unique");
            return DSL_RESULT_DISPLAY_NAME_NOT_UNIQUE;
        }
        try
        {
            m_components[name] = std::shared_ptr<Bintr>(new DisplayBintr(
                name, width, height));
        }
        catch(...)
        {
            LOG_ERROR("Tiled Display New'" << name << "' threw exception on create");
            return DSL_RESULT_DISPLAY_NEW_EXCEPTION;
        }
        LOG_INFO("new Display '" << name << "' created successfully");

        return DSL_RESULT_SUCCESS;
    }
        
    DslReturnType Services::PrimaryGieNew(const char* name, const char* inferConfigFile,
        const char* modelEngineFile, uint interval, uint uniqueId)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        // ensure component name uniqueness 
        if (m_components[name])
        {   
            LOG_ERROR("GIE name '" << name << "' is not unique");
            return DSL_RESULT_GIE_NAME_NOT_UNIQUE;
        }
        
        LOG_INFO("Infer config file: " << inferConfigFile);
        
        std::ifstream configFile(inferConfigFile);
        if (!configFile.good())
        {
            LOG_ERROR("Infer Config File not found");
            return DSL_RESULT_GIE_CONFIG_FILE_NOT_FOUND;
        }
        
        LOG_INFO("Model engine file: " << modelEngineFile);
        
        std::ifstream modelFile(modelEngineFile);
        if (!modelFile.good())
        {
            LOG_ERROR("Model Engine File not found");
            return DSL_RESULT_GIE_MODEL_FILE_NOT_FOUND;
        }

        try
        {
            m_components[name] = DSL_PRIMARY_GIE_NEW(name, 
                inferConfigFile, modelEngineFile, interval, uniqueId);
        }
        catch(...)
        {
            LOG_ERROR("New Primary GIE '" << name << "' threw exception on create");
            return DSL_RESULT_GIE_NEW_EXCEPTION;
        }
        LOG_INFO("new GIE '" << name << "' created successfully");

        return DSL_RESULT_SUCCESS;
    }
    
    DslReturnType Services::ComponentDelete(const char* component)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_COMPONENT_NAME_NOT_FOUND(m_components, component);
        
        if (m_components[component]->IsInUse())
        {
            LOG_INFO("Component '" << component << "' is in use");
            return DSL_RESULT_COMPONENT_IN_USE;
        }

        m_components.erase(component);

        LOG_INFO("Component '" << component << "' deleted successfully");

        return DSL_RESULT_SUCCESS;
    }
    
    DslReturnType Services::ComponentDeleteMany(const char** components)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        // iterate through the list of provided components to verifiy the
        // existence of each... AND that each is not owned by a pipeline 
        // before making any updates to the list of components.
        for (const char** component = components; *component; component++)
        {
            RETURN_IF_COMPONENT_NAME_NOT_FOUND(m_components, *component);

            if (m_components[*component]->IsInUse())
            {   
                LOG_ERROR("Component '" << *component << "' is currently in use");
                return DSL_RESULT_COMPONENT_IN_USE;
            }
        }
        LOG_DEBUG("All listed components found and un-owned");
        
        // iterate through the list a second time erasing each
        for (const char** component = components; *component; component++)
        {
            m_components.erase(*component);
        }

        LOG_INFO("All Components deleted successfully");

        return DSL_RESULT_SUCCESS;
    }

    DslReturnType Services::ComponentDeleteAll()
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        
        for (auto const& imap: m_components)
        {
            if (imap.second->IsInUse())
            {
                LOG_ERROR("Component '" << imap.second->m_name << "' is currently in use");
                return DSL_RESULT_COMPONENT_IN_USE;
            }
        }
        LOG_DEBUG("All components are un-owned and will be deleted");

        for (auto const& imap: m_components)
        {
            m_components.erase(imap.second->m_name);
        }
        LOG_INFO("All Components deleted successfully");

        return DSL_RESULT_SUCCESS;
    }

    uint Services::ComponentListSize()
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        
        return m_components.size();
    }
    
    const char** Services::ComponentListAll()
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        
        m_componentNames.clear();
        
        // reserve to avoid resizing - plus 1 for the NULL terminator
        m_componentNames.reserve(m_components.size() + 1);
        for(auto const& imap: m_components)
        {
            m_componentNames.push_back(imap.first.c_str());
        }
        m_componentNames.push_back(NULL);
        
        return (const char**)&m_componentNames[0];
    }
    
    DslReturnType Services::PipelineNew(const char* pipeline)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        if (m_pipelines[pipeline])
        {   
            LOG_ERROR("Pipeline name '" << pipeline << "' is not unique");
            return DSL_RESULT_PIPELINE_NAME_NOT_UNIQUE;
        }
        try
        {
            m_pipelines[pipeline] = std::shared_ptr<PipelineBintr>(new PipelineBintr(pipeline));
        }
        catch(...)
        {
            LOG_ERROR("New Pipeline '" << pipeline << "' threw exception on create");
            return DSL_RESULT_PIPELINE_NEW_EXCEPTION;
        }
        LOG_INFO("new PIPELINE '" << pipeline << "' created successfully");

        return DSL_RESULT_SUCCESS;
    }

    DslReturnType Services::PipelineNewMany(const char** pipelines)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        for (const char** pipeline = pipelines; *pipeline; pipeline++)
        {
            if (m_pipelines[*pipeline])
            {   
                LOG_ERROR("Pipeline name '" << *pipeline << "' is not unique");
                return DSL_RESULT_PIPELINE_NAME_NOT_UNIQUE;
            }
            try
            {
                m_pipelines[*pipeline] = std::shared_ptr<PipelineBintr>(new PipelineBintr(*pipeline));
            }
            catch(...)
            {
                LOG_ERROR("New Pipeline '" << *pipeline << "' threw exception on create");
                return DSL_RESULT_PIPELINE_NEW_EXCEPTION;
            }
            LOG_INFO("new PIPELINE '" << *pipeline << "' created successfully");
        }
    }
    
    DslReturnType Services::PipelineDelete(const char* pipeline)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);

        m_pipelines[pipeline]->RemoveAllChildren();
        m_pipelines.erase(pipeline);

        LOG_INFO("Pipeline '" << pipeline << "' deleted successfully");

        return DSL_RESULT_SUCCESS;
    }

    DslReturnType Services::PipelineDeleteMany(const char** pipelines)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        // iterate through the list of provided pipelines to verifiy the
        // existence of each before making any updates to the list of pipelines.
        for (const char** pipeline = pipelines; *pipeline; pipeline++)
        {
            RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, *pipeline);
        }
        LOG_DEBUG("All listed pipelines found");
        
        // iterate through the list a second time erasing each
        for (const char** pipeline = pipelines; *pipeline; pipeline++)
        {
            m_pipelines[*pipeline]->RemoveAllChildren();
            m_pipelines.erase(*pipeline);
        }

        LOG_INFO("All Pipelines deleted successfully");

        return DSL_RESULT_SUCCESS;
    }

    DslReturnType Services::PipelineDeleteAll()
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        for (auto &imap: m_pipelines)
        {
            imap.second->RemoveAllChildren();
            imap.second = nullptr;
        }
        m_pipelines.clear();

        return DSL_RESULT_SUCCESS;
    }

    uint Services::PipelineListSize()
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        
        return m_pipelines.size();
    }
    
    const char** Services::PipelineListAll()
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        
        m_pipelineNames.clear();
        
        // reserve to avoid resizing - plus 1 for the NULL terminator
        m_pipelineNames.reserve(m_pipelines.size() + 1);
        for(auto const& imap: m_pipelines)
        {
            m_pipelineNames.push_back(imap.first.c_str());
        }
        m_pipelineNames.push_back(NULL);
        
        return (const char**)&m_pipelineNames[0];
    }
    
    DslReturnType Services::PipelineComponentAdd(const char* pipeline, 
        const char* component)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);
        RETURN_IF_COMPONENT_NAME_NOT_FOUND(m_components, component);

        try
        {
            m_components[component]->AddToParent(m_pipelines[pipeline]);
            LOG_INFO("Component '" << component 
                << "' was added to Pipeline '" << pipeline << "' successfully");
        }
        catch(...)
        {
            LOG_ERROR("Pipeline '" << pipeline 
                << "' threw exception adding component '" << component << "'");
            return DSL_RESULT_PIPELINE_COMPONENT_ADD_FAILED;
        }
    }    
        
    
    DslReturnType Services::PipelineComponentAddMany(const char* pipeline, 
        const char** components)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);
        
        // iterate through the list of provided components to verifiy the
        //  existence of each - before making any updates to the pipeline.
        for (const char** component = components; *component; component++)
        {
            RETURN_IF_COMPONENT_NAME_NOT_FOUND(m_components, *component);
        }
        LOG_DEBUG("All listed components found");
        
        // iterate through the list of provided components a second time
        // adding each to the named pipeline individually.
        for (const char** component = components; *component; component++)
        {
            try
            {
                m_components[*component]->AddToParent(m_pipelines[pipeline]);
                LOG_INFO("Component '" << *component 
                    << "' was added to Pipeline '" << pipeline << "' successfully");
            }
            catch(...)
            {
                LOG_ERROR("Pipeline '" << pipeline 
                    << "' threw exception adding component '" << *component << "'");
                return DSL_RESULT_PIPELINE_COMPONENT_ADD_FAILED;
            }
        }
        
        return DSL_RESULT_SUCCESS;
    }

    DslReturnType Services::PipelineComponentRemove(const char* pipeline, 
        const char* component)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);
        RETURN_IF_COMPONENT_NAME_NOT_FOUND(m_components, component);

        if (!m_components[component]->IsParent(m_pipelines[pipeline]))
        {
            LOG_ERROR("Component '" << component << 
                "' is not in use by Pipeline '" << pipeline << "'");
            return DSL_RESULT_COMPONENT_NOT_USED_BY_PIPELINE;
        }
        try
        {
            m_components[component]->RemoveFromParent(m_pipelines[pipeline]);
        }
        catch(...)
        {
            LOG_ERROR("Pipeline '" << pipeline 
                << "' threw an exception removing component");
            return DSL_RESULT_PIPELINE_COMPONENT_REMOVE_FAILED;
        }
        return DSL_RESULT_SUCCESS;
}
    
    DslReturnType Services::PipelineComponentRemoveMany(const char* pipeline, 
        const char** components)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);

        return DSL_RESULT_API_NOT_IMPLEMENTED;
    }
    
    DslReturnType Services::PipelineStreamMuxSetBatchProperties(const char* pipeline,
        uint batchSize, uint batchTimeout)    
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);

        try
        {
            m_pipelines[pipeline]->SetStreamMuxBatchProperties(batchSize, batchTimeout);
        }
        catch(...)
        {
            LOG_ERROR("Pipeline '" << pipeline 
                << "' threw an exception setting the Stream Muxer batch_properties");
            return DSL_RESULT_PIPELINE_STREAMMUX_SET_FAILED;
        }
        return DSL_RESULT_SUCCESS;
    }

    DslReturnType Services::PipelineStreamMuxSetOutputSize(const char* pipeline,
        uint width, uint height)    
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);

        try
        {
            m_pipelines[pipeline]->SetStreamMuxOutputSize(width, height);
        }
        catch(...)
        {
            LOG_ERROR("Pipeline '" << pipeline 
                << "' threw an exception setting the Stream Muxer output size");
            return DSL_RESULT_PIPELINE_STREAMMUX_SET_FAILED;
        }
        return DSL_RESULT_SUCCESS;
    }
        
    DslReturnType Services::PipelinePause(const char* pipeline)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);

        return DSL_RESULT_API_NOT_IMPLEMENTED;
    }

    DslReturnType Services::PipelinePlay(const char* pipeline)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);

        if (!std::dynamic_pointer_cast<PipelineBintr>(m_pipelines[pipeline])->Play())
        {
            return DSL_RESULT_PIPELINE_FAILED_TO_PLAY;
        }

        return DSL_RESULT_SUCCESS;
    }
    
    DslReturnType Services::PipelineGetState(const char* pipeline)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);

        return DSL_RESULT_API_NOT_IMPLEMENTED;
    }
        
    DslReturnType Services::PipelineDumpToDot(const char* pipeline, char* filename)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
    
        if (!m_pipelines[pipeline])
        {   
            LOG_ERROR("Pipeline name '" << pipeline << "' was not found");
            return DSL_RESULT_PIPELINE_NAME_NOT_FOUND;
        }
        // TODO check state of debug env var and return NON-success if not set

        m_pipelines[pipeline]->DumpToDot(filename);
        
        return DSL_RESULT_SUCCESS;
    }   
    
    DslReturnType Services::PipelineDumpToDotWithTs(const char* pipeline, char* filename)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);

        // TODO check state of debug env var and return NON-success if not set

        m_pipelines[pipeline]->DumpToDot(filename);

        return DSL_RESULT_SUCCESS;
    }

    DslReturnType Services::PipelineStateChangeListenerAdd(const char* pipeline, 
        dsl_state_change_listener_cb listener, void* userdata)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);

        if (m_pipelines[pipeline]->IsChildStateChangeListener(listener))
        {
            return DSL_RESULT_PIPELINE_LISTENER_NOT_UNIQUE;
        }
        return m_pipelines[pipeline]->AddStateChangeListener(listener, userdata);
    }
        
    DslReturnType Services::PipelineStateChangeListenerRemove(const char* pipeline, 
        dsl_state_change_listener_cb listener)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);
    
        if (!m_pipelines[pipeline]->IsChildStateChangeListener(listener))
        {
            return DSL_RESULT_PIPELINE_LISTENER_NOT_FOUND;
        }
        return m_pipelines[pipeline]->RemoveStateChangeListener(listener);
    }
    
    DslReturnType Services::PipelineDisplayEventHandlerAdd(const char* pipeline, 
        dsl_display_event_handler_cb handler, void* userdata)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);
        
        if (m_pipelines[pipeline]->IsChildDisplayEventHandler(handler))
        {
            return DSL_RESULT_PIPELINE_HANDLER_NOT_UNIQUE;
        }
        return m_pipelines[pipeline]->AddDisplayEventHandler(handler, userdata);
    }
        

    DslReturnType Services::PipelineDisplayEventHandlerRemove(const char* pipeline, 
        dsl_display_event_handler_cb handler)
    {
        LOG_FUNC();
        LOCK_MUTEX_FOR_CURRENT_SCOPE(&m_servicesMutex);
        RETURN_IF_PIPELINE_NAME_NOT_FOUND(m_pipelines, pipeline);
        
        if (!m_pipelines[pipeline]->IsChildDisplayEventHandler(handler))
        {
            return DSL_RESULT_PIPELINE_HANDLER_NOT_FOUND;
        }
        return m_pipelines[pipeline]->RemoveDisplayEventHandler(handler);
    }
    

} // namespace 