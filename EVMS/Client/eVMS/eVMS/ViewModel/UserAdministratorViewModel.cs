using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using eVMS.Jsoncontract;
using eVMS.Model;
using Newtonsoft.Json;

namespace eVMS.ViewModel
{
    public class UserAdministratorViewModel:ViewModelBase
    {

        #region Properties
        //All user item
        private ObservableCollection<PersonViewModel> _allUserItem;
        public ObservableCollection<PersonViewModel> AllUserItem
        {
            get { return _allUserItem; }
            set
            {
                if (_allUserItem != value)
                {
                    _allUserItem = value;
                    RaisePropertyChanged(() => AllUserItem);
                }
            }
        }

        private PersonViewModel _selectionItem;
        public PersonViewModel SelectionItem {
            get { return _selectionItem; }
            set {
                if (_selectionItem != value)
                {
                    _selectionItem = value;
                    RaisePropertyChanged(()=>SelectionItem);
                }
            }
        }

        private bool _isSelectItem;

        public bool IsSelectItem
        {
            get { return _isSelectItem; }
            set {
                if (_isSelectItem != value)
                {
                    _isSelectItem = value;
                    RaisePropertyChanged(()=>IsSelectItem);
                }
            }
        }


        //private List<String> _Sex;

        //public List<String> Property
        //{
        //    get
        //    {
        //        return new List<string>() {"string1", "string2"};
        //    }
        //    set { _property = value; }
        //}

        //public String SimpleStringProperty{get;set;}
        #endregion

        #region Contructors

        public UserAdministratorViewModel()
        {
            _allUserItem = new ObservableCollection<PersonViewModel>();
            IsSelectItem = false;
        }

        public UserAdministratorViewModel(ObservableCollection<PersonViewModel> listPerson):this()
        {
            AllUserItem = listPerson;
        }

        #endregion

        #region Method

        public void InitTemp()
        {
            //AllUserItem.Add(new PersonViewModel(){FullName = "Le hoang",Birthday = DateTime.Today, Phone = "01665676265" ,Role = "Admin",Sex = "Man",UserId = 1});
            //AllUserItem.Add(new PersonViewModel() { FullName = "Le hoang", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Man", UserId = 2 });
            //AllUserItem.Add(new PersonViewModel() { FullName = "Le hoang", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Man", UserId = 3 });
            //AllUserItem.Add(new PersonViewModel() { FullName = "Le hoang", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Man", UserId = 4 });
            //AllUserItem.Add(new PersonViewModel() { FullName = "Le hoang", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Man", UserId = 5 });
            //AllUserItem.Add(new PersonViewModel() { FullName = "Le hoang", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Man", UserId = 6 });
            //AllUserItem.Add(new PersonViewModel() { FullName = "Le hoang", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Man", UserId = 7 });
            //AllUserItem.Add(new PersonViewModel() { FullName = "Le hoang", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Man", UserId = 8 });
            //AllUserItem.Add(new PersonViewModel() { FullName = "Le hoang", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Man", UserId = 9 });
            //AllUserItem.Add(new PersonViewModel() { FullName = "Le hoang", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Man", UserId = 10 });

            //Test create new json
            //List<Person> list = new List<Person>();
            //list.Add(new Person() { FullName = "Lehoang1", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Nam", UserId = 1 });
            //list.Add(new Person() { FullName = "Lehoang2", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Nữ", UserId = 2 });
            //list.Add(new Person() { FullName = "Lehoang3", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Nam", UserId = 3 });
            //list.Add(new Person() { FullName = "Lehoang4", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Nữ", UserId = 4 });
            //list.Add(new Person() { FullName = "Lehoang5", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Nữ", UserId = 5 });
            //list.Add(new Person() { FullName = "Lehoang6", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Nữ", UserId = 6 });
            //list.Add(new Person() { FullName = "Lehoang7", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Nữ", UserId = 7 });
            //list.Add(new Person() { FullName = "Lehoang8", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Nữ", UserId = 8 });
            //list.Add(new Person() { FullName = "Lehoang9", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Nữ", UserId = 9 });
            //list.Add(new Person() { FullName = "Lehoang10", Birthday = DateTime.Today, Phone = "01665676265", Role = "Admin", Sex = "Nữ", UserId = 10 });

            //AccountList accountList = new AccountList();
            //accountList.Allaccount = list;
            //string json = JsonConvert.SerializeObject(accountList);
            //var data = JsonConvert.DeserializeObject<AccountList>(json);
            //if (data != null && data is AccountList)
            //{
            //    foreach (var person in (data.Allaccount as List<Person>))
            //    {
            //        AllUserItem.Add(new PersonViewModel() 
            //        { 
            //            FullName = person.FullName, 
            //            Birthday = person.Birthday, 
            //            Phone = person.Phone, 
            //            Role = person.Role, 
            //            Sex = person.Sex, 
            //            UserId = person.UserId
            //        });
            //    }
            //}
            //End test
        }

        

        #endregion
    }
}
