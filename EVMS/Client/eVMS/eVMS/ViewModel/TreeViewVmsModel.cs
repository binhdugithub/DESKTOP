using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using eVMS.Jsoncontract;
using eVMS.Utils;
using eVMS.VMS;
using Newtonsoft.Json;

namespace eVMS.ViewModel
{
    class TreeViewVmsModel : ViewModelBase
    {
        private ObservableCollection<VmsMembers> _vmsMems;
        private VmsMembers _selectedItem;
        public List<String> VmsOnServerMembersList = new List<string>();
        public VmsMembers SelectedItem
        {
            get { return _selectedItem; }
            set
            {
                if (_selectedItem != value)
                {
                    _selectedItem = value;
                    RaisePropertyChanged(() => SelectedItem);

                }
            }
        }

        private VmsObject _selectedchildItem;
        public VmsObject SelectedChildItem
        {
            get { return _selectedchildItem; }
            set
            {
                _selectedchildItem = value;
                RaisePropertyChanged(() => SelectedChildItem);
            }
        }
        public ObservableCollection<VmsMembers> VmsMems
        {
            get { return _vmsMems; }
            set
            {
                if (_vmsMems != value)
                {
                    _vmsMems = value;
                    RaisePropertyChanged(() => VmsMems);
                }
            }
        }

        public TreeViewVmsModel()
        {
            VmsMems = new ObservableCollection<VmsMembers>();
        }

        public void SetViewModel(List<Model.Vms> listVms)
        {
            if(listVms == null)
                return;
            
            var AllMembers = new ObservableCollection<VmsMembers>();
            foreach (var vms in listVms)
            {
                int wi, he = 0;
                int.TryParse(vms.height, out he);
                int.TryParse(vms.width, out wi);
                if (wi == 0)
                    wi = 450;
                if (he == 0)
                    he = 200;
                VmsMembers mem1 = new VmsMembers() { Name = vms.name, VmsId = vms.id, Height = he, Width = wi ,nColor = vms.nColor};

                if (vms.program != string.Empty)
                {
                    try
                    {
                        var res = JsonConvert.DeserializeObject<Desiprogram>(vms.program);
                        if(res == null)
                            continue;
                        foreach (var vmsMemberse in res.image)
                        {
                            string imglink = vmsMemberse.link.Replace("-", "\\");
                            var iamgeobj = new VmsImage()
                            {
                                Avatar = "addpicture",
                                Height = vmsMemberse.height,
                                Width = vmsMemberse.width,
                                ImageLink = imglink,
                                Name = vmsMemberse.name,
                                X = vmsMemberse.x,
                                Y = vmsMemberse.y
                            };

                            mem1.Members.Add(iamgeobj);
                        }
                        foreach (var text in res.text)
                        {
                            
                            var textobj = new VmsText()
                            {
                                Avatar = "addtext",
                                FontFamily = text.font,
                                FontSize = (text.fontsize == null) ? "1" : text.fontsize,
                                Height = text.height,
                                Width = text.width,
                                
                                X = text.x,
                                Y= text.y,
                                Content = text.content,
                                FontStyle = (text.fontstyle == "Italic")?true:false,
                                FontWight = (text.fontweight == "Bold")?true:false,
                                Name = text.name,
                                ColorText = text.colortext

                            };
                            mem1.Members.Add(textobj);
                        }
                    }
                    catch (Exception ex)
                    {
                        Log4Net.Log.Error(ex);
                        
                    }
                    
                }
                
                AllMembers.Add(mem1);
                
                VmsOnServerMembersList.Add(mem1.Name);
            }
            
            VmsMems = AllMembers;
            
        }
    }
}
