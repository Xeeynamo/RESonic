using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using XeLib;

namespace ObjectEditor
{
    public class Entity
    {
        EntityProperties m_properties = new EntityProperties();
        Physic m_physic = new Physic();
        Animation m_animation = new Animation();

        public void Load(FileStreamEx f)
        {
            m_properties.Load(f);
            m_physic.Load(f);
            m_animation.Load(f);
        }
        public void Save(FileStreamEx f)
        {
            m_properties.Save(f);
            m_physic.Save(f);
            m_animation.Save(f);
        }

        public EntityProperties Properties
        {
            get
            {
                return m_properties;
            }
        }
        public Physic Physic
        {
            get
            {
                return m_physic;
            }
        }
        public Animation Animation
        {
            get
            {
                return m_animation;
            }
        }
    }
}
