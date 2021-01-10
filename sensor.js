var firebaseConfig = {
    apiKey: "AIzaSyAckAS7Fn858QdmoR08eQZXM9W3ePeFDPQ",
    authDomain: "gocorona-84a11.firebaseapp.com",
    databaseURL: "https://gocorona-84a11.firebaseio.com",
    projectId: "gocorona-84a11",
    storageBucket: "gocorona-84a11.appspot.com",
    messagingSenderId: "416138584360",
    appId: "1:416138584360:web:cc37c4820a4c012fca301d",
    measurementId: "G-B9X15C5R6P"
  };
  // Initialize Firebase
  firebase.initializeApp(firebaseConfig);
  var database = firebase.database();
  var ques = database.ref().child('Soil moisture');



ques.on("child_added", function(snapshot, prevChildKey) {
    var newReading = snapshot.val();
    var table = document.getElementById("myTable");
    var row = table.insertRow();
    var cell1 = row.insertCell(0);
    cell1.innerHTML = newReading;
     Plotly.plot('chart',[{
                y:[newReading],
                type:'line'
            }]);
            
            var cnt = 0;
            setInterval(function(){
                Plotly.extendTraces('chart',{ y:[[newReading]]}, [0]);
                cnt++;
                if(cnt > 10) {
                    Plotly.relayout('chart',{
                        xaxis: {
                            range: [cnt-10,cnt]
                        }
                    }
                );}
            },1000);
  });

function clear(){
    var db = database.ref();
    ref.child("/Soil moisture").remove();
}
